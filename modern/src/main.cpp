#include "raylib.h"
#include "Simulation.h"
#include "ClassicUI.h"
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

using namespace ClassicUI;

// Scale factor: 1.7x larger screen as requested by user
static const float SCALE = 1.7f;
static inline float S(float v) { return roundf(v * SCALE); }
static inline int   S(int v)   { return (int)roundf((float)v * SCALE); }

// Virtual canvas dimensions (1.7x original 752x438)
static const int VIRTUAL_W = 1280;
static const int VIRTUAL_H = 748;

// Helper to load BMP sprites with Magenta colorkey (clFuchsia 0xFF00FF) transparency
static Texture2D LoadTransparentBMP(const char* path1, const char* path2) {
    Image img = { 0 };
    if (FileExists(path1)) {
        img = LoadImage(path1);
    } else if (FileExists(path2)) {
        img = LoadImage(path2);
    }

    if (img.data != nullptr) {
        ImageColorReplace(&img, Color{ 255, 0, 255, 255 }, BLANK);
        Texture2D tex = LoadTextureFromImage(img);
        UnloadImage(img);
        return tex;
    }
    return Texture2D{};
}

int main() {
    // Initial window size matches virtual canvas
    const int startWindowW = 1280;
    const int startWindowH = 748;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(startWindowW, startWindowH, "Australia 1859 Sim - Island Ecosystem Simulator (Dawid Domagala)");
    SetWindowMinSize(960, 560);
    SetTargetFPS(60);

    // Initialize ClassicUI with 1.7x scaling and Tahoma Regular TrueType font
    ClassicUI::Init(SCALE, "assets/tahoma.ttf");

    // RenderTexture for fixed virtual resolution and pixel-perfect letterbox scaling
    RenderTexture2D target = LoadRenderTexture(VIRTUAL_W, VIRTUAL_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    Simulation sim;

    // RGBA buffer for procedural 500x400 island map
    std::vector<uint8_t> rgbaBuffer(Simulation::SZER * Simulation::WYS * 4, 255);
    Image islandImage = {
        rgbaBuffer.data(),
        Simulation::SZER,
        Simulation::WYS,
        1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture2D islandTexture = LoadTextureFromImage(islandImage);

    // Load authentic animal sprites
    Texture2D texKrolik  = LoadTransparentBMP("assets/krolik.bmp", "krolik.bmp");
    Texture2D texLis     = LoadTransparentBMP("assets/lis.bmp", "lis.bmp");
    Texture2D texWybrany = LoadTransparentBMP("assets/wybrany.bmp", "wybrany.bmp");

    // Speed multiplier & accumulator
    float speedMultiplier = 1.0f; // 0.25x, 0.5x, 1.0x, 2.0x, 5.0f, 10.0f
    float simAccumulator = 0.0f;

    while (!WindowShouldClose()) {
        // --- Fullscreen toggle (F11) ---
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        // Global hotkeys
        if (IsKeyPressed(KEY_SPACE)) {
            if (sim.poziom == 1) {
                sim.running = !sim.running;
            } else {
                sim.butOkClick();
            }
        }
        if (IsKeyPressed(KEY_ONE))   speedMultiplier = 1.0f;
        if (IsKeyPressed(KEY_TWO))   speedMultiplier = 2.0f;
        if (IsKeyPressed(KEY_THREE)) speedMultiplier = 5.0f;
        if (IsKeyPressed(KEY_FOUR))  speedMultiplier = 10.0f;
        if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)) {
            if (speedMultiplier > 1.0f) speedMultiplier -= 1.0f;
            else if (speedMultiplier > 0.5f) speedMultiplier = 0.5f;
            else if (speedMultiplier > 0.25f) speedMultiplier = 0.25f;
        }
        if (IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD)) {
            if (speedMultiplier < 0.5f) speedMultiplier = 0.5f;
            else if (speedMultiplier < 1.0f) speedMultiplier = 1.0f;
            else if (speedMultiplier < 10.0f) speedMultiplier += 1.0f;
        }

        // Step simulation logic with variable speed control
        if (sim.running) {
            simAccumulator += speedMultiplier;
            while (simAccumulator >= 1.0f) {
                sim.update();
                simAccumulator -= 1.0f;
            }
        }

        // Refresh island terrain texture
        sim.renderToRGBA(rgbaBuffer.data());
        UpdateTexture(islandTexture, rgbaBuffer.data());

        // Compute letterbox aspect ratio and virtual mouse coordinates
        float screenW = (float)GetScreenWidth();
        float screenH = (float)GetScreenHeight();
        float scale = fminf(screenW / (float)VIRTUAL_W, screenH / (float)VIRTUAL_H);
        float offsetX = (screenW - ((float)VIRTUAL_W * scale)) * 0.5f;
        float offsetY = (screenH - ((float)VIRTUAL_H * scale)) * 0.5f;

        Vector2 screenMouse = GetMousePosition();
        Vector2 vMouse = {
            (screenMouse.x - offsetX) / scale,
            (screenMouse.y - offsetY) / scale
        };
        ClassicUI::SetVirtualMouse(vMouse);

        // Map layout constants (scaled 1.7x)
        const float mapLeft = 14.0f;
        const float mapTop  = 14.0f;
        const float mapW    = (float)Simulation::SZER * SCALE; // 850px
        const float mapH    = (float)Simulation::WYS * SCALE;  // 680px

        // Select rabbit / fox by clicking on the scaled map
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && sim.poziom == 1) {
            int mx = (int)((vMouse.x - mapLeft) / SCALE);
            int my = (int)((vMouse.y - mapTop) / SCALE);
            if (mx >= 0 && mx < Simulation::SZER && my >= 0 && my < Simulation::WYS) {
                int bestK = -1;
                float bestDistK = 18.0f;
                for (size_t i = 0; i < sim.Ktab.size(); i++) {
                    float d = hypotf((float)(sim.Ktab[i].x - mx), (float)(sim.Ktab[i].y - my));
                    if (d < bestDistK) {
                        bestDistK = d;
                        bestK = (int)i;
                    }
                }

                int bestL = -1;
                float bestDistL = 18.0f;
                for (size_t i = 0; i < sim.Ltab.size(); i++) {
                    float d = hypotf((float)(sim.Ltab[i].x - mx), (float)(sim.Ltab[i].y - my));
                    if (d < bestDistL) {
                        bestDistL = d;
                        bestL = (int)i;
                    }
                }

                if (bestL >= 0 && bestDistL <= bestDistK) {
                    sim.selectedLisIdx = bestL;
                    sim.activeInformerTab = 5; // "My Fox" tab
                } else if (bestK >= 0) {
                    sim.selectedKrolikIdx = bestK;
                    sim.activeInformerTab = 4; // "My Rabbit" tab
                }
            }
        }

        // =========================================================================
        // DRAW TO VIRTUAL RENDER TARGET (1280 x 748)
        // =========================================================================
        BeginTextureMode(target);
        ClearBackground(CLR_BG);

        // 1. 850x680 Island map in a classic 3D sunken border
        Rectangle mapBorder = { mapLeft - 3.0f, mapTop - 3.0f, mapW + 6.0f, mapH + 6.0f };
        DrawSunkenBox(mapBorder, BLACK);
        DrawTextureEx(islandTexture, Vector2{ mapLeft, mapTop }, 0.0f, SCALE, WHITE);

        // Draw rabbits (switch to fast crisp points when > 1000 to maintain 60 FPS!)
        bool fastDotsK = (sim.Ktab.size() > 1000);
        int dotSizeK = (int)roundf(2.5f * SCALE);
        for (const auto& k : sim.Ktab) {
            float kx = mapLeft + k.x * SCALE;
            float ky = mapTop  + k.y * SCALE;
            if (!fastDotsK && texKrolik.id != 0) {
                DrawTextureEx(texKrolik, Vector2{ kx - 2.0f * SCALE, ky - 2.0f * SCALE }, 0.0f, SCALE, WHITE);
            } else {
                DrawRectangle((int)kx, (int)ky, dotSizeK, dotSizeK, WHITE);
            }
        }

        // Draw foxes (switch to fast crisp points when > 200)
        bool fastDotsL = (sim.Ltab.size() > 200);
        int dotSizeL = (int)roundf(3.5f * SCALE);
        for (const auto& l : sim.Ltab) {
            float lx = mapLeft + l.x * SCALE;
            float ly = mapTop  + l.y * SCALE;
            if (!fastDotsL && texLis.id != 0) {
                DrawTextureEx(texLis, Vector2{ lx - 2.0f * SCALE, ly - 2.0f * SCALE }, 0.0f, SCALE, WHITE);
            } else {
                DrawRectangle((int)lx, (int)ly, dotSizeL, dotSizeL, RED);
            }
        }

        // Highlight selected animal
        if (sim.poziom == 1) {
            if (sim.activeInformerTab == 4 && sim.selectedKrolikIdx >= 0 && sim.selectedKrolikIdx < (int)sim.Ktab.size()) {
                const auto& selK = sim.Ktab[sim.selectedKrolikIdx];
                float sx = mapLeft + selK.x * SCALE;
                float sy = mapTop  + selK.y * SCALE;
                if (texWybrany.id != 0) {
                    DrawTextureEx(texWybrany, Vector2{ sx - 3.0f * SCALE, sy - 3.0f * SCALE }, 0.0f, SCALE, WHITE);
                } else {
                    DrawRectangleLines((int)(sx - 4.0f * SCALE), (int)(sy - 4.0f * SCALE), (int)(9.0f * SCALE), (int)(9.0f * SCALE), YELLOW);
                }
            } else if (sim.activeInformerTab == 5 && sim.selectedLisIdx >= 0 && sim.selectedLisIdx < (int)sim.Ltab.size()) {
                const auto& selL = sim.Ltab[sim.selectedLisIdx];
                float sx = mapLeft + selL.x * SCALE;
                float sy = mapTop  + selL.y * SCALE;
                if (texWybrany.id != 0) {
                    DrawTextureEx(texWybrany, Vector2{ sx - 3.0f * SCALE, sy - 3.0f * SCALE }, 0.0f, SCALE, WHITE);
                } else {
                    DrawRectangleLines((int)(sx - 4.0f * SCALE), (int)(sy - 4.0f * SCALE), (int)(9.0f * SCALE), (int)(9.0f * SCALE), YELLOW);
                }
            }
        }

        // 2. Control Panel on right (Upper part)
        const float panelX = mapLeft + mapW + 14.0f; // 878px
        const float panelY = 14.0f;
        const float panelW = (float)VIRTUAL_W - panelX - 14.0f; // 388px
        const float panelH = 584.0f; // Dedicated vertical space prevents any overlap!
        Rectangle groupBoxRect = { panelX, panelY, panelW, panelH };

        // -------------------------------------------------------------------------
        // PHASE 1: Island Generator
        // -------------------------------------------------------------------------
        if (sim.poziom == 0) {
            DrawGroupBox(groupBoxRect, "Island Generator ver. 1.4");

            const char* godTabs[] = { "Shape", "Bays", "Adjust", "Terrain" };
            Rectangle tabRect = { panelX + 8.0f, panelY + 20.0f, panelW - 16.0f, 28.0f };
            sim.activeGodTab = DrawTabs(tabRect, godTabs, 4, sim.activeGodTab);

            float rowW = panelW - 24.0f;
            float startX = panelX + 12.0f;
            float baseY = panelY + 60.0f;

            if (sim.activeGodTab == 0) { // Shape
                DrawNumericRow(startX, baseY + 10.0f, rowW, "Shape Amplitude", sim.amplitude, 1, 1000, 5);

                if (DrawButton({ startX + 10.0f, baseY + 50.0f, rowW - 20.0f, 32.0f }, "Generate Island")) {
                    sim.generujWyspe(sim.amplitude);
                }

                DrawLabel(startX + 4.0f, baseY + 104.0f, "Set shape amplitude and click\n'Generate Island' to forge\na new island boundary.\n\nThen use Bays & Adjust to sculpt.", 10, CLR_TEXT);
            }
            else if (sim.activeGodTab == 1) { // Bays
                DrawNumericRow(startX, baseY + 10.0f, rowW, "Bay Count", sim.upDownLzatok, 1, 99);
                DrawNumericRow(startX, baseY + 44.0f, rowW, "Bay Size", sim.upDownWZatok, 1, 1000, 5);
                DrawNumericRow(startX, baseY + 78.0f, rowW, "Irregularity", sim.upDownRZatok, 0, 999, 5);

                if (DrawButton({ startX + 10.0f, baseY + 120.0f, rowW - 20.0f, 30.0f }, "Carve Deep Bays")) {
                    sim.dodajZatoki(sim.upDownLzatok, sim.upDownWZatok, sim.upDownRZatok);
                }
                if (DrawButton({ startX + 10.0f, baseY + 158.0f, rowW - 20.0f, 30.0f }, "Carve Coastal Bays")) {
                    sim.dodajZatokiPlaza(sim.upDownLzatok, sim.upDownWZatok, sim.upDownRZatok);
                }
            }
            else if (sim.activeGodTab == 2) { // Adjust
                DrawLabel(startX + 14.0f, baseY + 10.0f, "Expand (+)", 10, CLR_NAVY);
                if (DrawButton({ startX + 10.0f, baseY + 28.0f, 74.0f, 34.0f }, "+")) {
                    sim.zwiekszLad();
                }

                DrawLabel(startX + 124.0f, baseY + 10.0f, "Shrink (-)", 10, CLR_NAVY);
                if (DrawButton({ startX + 120.0f, baseY + 28.0f, 74.0f, 34.0f }, "-")) {
                    sim.zmniejszLad();
                }

                DrawNumericRow(startX, baseY + 80.0f, rowW, "Smoothing Pass", sim.upDownGladz, 1, 20);
                if (DrawButton({ startX + 10.0f, baseY + 120.0f, rowW - 20.0f, 30.0f }, "Smooth Coastline")) {
                    sim.wygladz(sim.upDownGladz);
                }
            }
            else if (sim.activeGodTab == 3) { // Terrain
                if (DrawNumericRow(startX, baseY + 10.0f, rowW, "Beach Width", sim.upDownPlaza, 0, 200, 5) ||
                    DrawNumericRow(startX, baseY + 44.0f, rowW, "Grass Zone", sim.upDownTrawa, 0, 200, 5) ||
                    DrawNumericRow(startX, baseY + 78.0f, rowW, "Snow Zone", sim.upDownSnieg, 0, 200, 5)) {
                    sim.pallad();
                }

                DrawNumericRow(startX, baseY + 112.0f, rowW, "Noise Grain", sim.upDownZiarno, 0, 16);

                if (DrawButton({ startX + 10.0f, baseY + 152.0f, rowW - 20.0f, 28.0f }, "Add Terrain Noise")) {
                    sim.dodajZiarno(sim.upDownZiarno);
                }
                if (DrawButton({ startX + 10.0f, baseY + 188.0f, rowW - 20.0f, 28.0f }, "Apply Palette")) {
                    sim.pallad();
                }
            }
        }

        // -------------------------------------------------------------------------
        // PHASE 2: Ecosystem Simulation & Object Management
        // -------------------------------------------------------------------------
        else if (sim.poziom == 1) {
            DrawGroupBox(groupBoxRect, "Ecosystem Manager ver. 1.4");
            float rowW = panelW - 24.0f;
            float startX = panelX + 12.0f;

            // Two-row MultiLine TabControl with unmistakable active tab styling
            const char* tabsRow1[] = { "Grass", "Rabbits", "Foxes", "Stats" };
            const char* tabsRow2[] = { "My Rabbit", "My Fox", "Evolution" };

            Rectangle tabR1 = { panelX + 8.0f, panelY + 18.0f, panelW - 16.0f, 26.0f };
            Rectangle tabR2 = { panelX + 8.0f, panelY + 44.0f, panelW - 16.0f, 26.0f };

            int curR1 = (sim.activeInformerTab < 4) ? sim.activeInformerTab : -1;
            int selR1 = DrawTabs(tabR1, tabsRow1, 4, curR1);
            if (selR1 != curR1 && selR1 >= 0) sim.activeInformerTab = selR1;

            int curR2 = (sim.activeInformerTab >= 4) ? (sim.activeInformerTab - 4) : -1;
            int selR2 = DrawTabs(tabR2, tabsRow2, 3, curR2);
            if (selR2 != curR2 && selR2 >= 0) sim.activeInformerTab = selR2 + 4;

            float baseY = panelY + 80.0f;

            if (sim.activeInformerTab == 0) { // Grass
                DrawNumericRow(startX, baseY + 10.0f, rowW, "Vegetation Rate", sim.wegetacja, 1, 100);

                if (DrawButton({ startX + 10.0f, baseY + 54.0f, rowW - 20.0f, 30.0f }, "Lush Grass (Max)")) {
                    sim.maxTrawa();
                }
                if (DrawButton({ startX + 10.0f, baseY + 94.0f, rowW - 20.0f, 30.0f }, "Reset Grass Level")) {
                    sim.resetTrawy();
                }
                if (DrawButton({ startX + 10.0f, baseY + 134.0f, rowW - 20.0f, 30.0f }, "Mow Grass (Min)")) {
                    sim.minTrawa();
                }

                DrawLabel(startX + 8.0f, baseY + 184.0f, "Lower vegetation rate = faster\ngrass growth across the island.", 10, CLR_TEXT);
            }
            else if (sim.activeInformerTab == 1) { // Rabbits
                DrawNumericRow(startX, baseY + 0.0f, rowW, "Spawn Count", sim.upDownIleK, 1, 999, 10);
                if (DrawButton({ startX + 8.0f, baseY + 28.0f, rowW - 16.0f, 26.0f }, "+ Spawn Rabbits Now")) {
                    sim.generujKroliki(sim.upDownIleK);
                }

                bool ch = false;
                ch |= DrawNumericRow(startX, baseY +  60.0f, rowW, "Speed (0.1x)", sim.vkVal, 1, 50, 1, "0.1x");
                ch |= DrawNumericRow(startX, baseY +  90.0f, rowW, "Metabolism", sim.metaKVal, 1, 50);
                ch |= DrawNumericRow(startX, baseY + 120.0f, rowW, "Grass Bite", sim.kesKVal, 1, 255);
                ch |= DrawNumericRow(startX, baseY + 150.0f, rowW, "Stomach Size", sim.zoladekKVal, 1, 1000, 5);
                ch |= DrawNumericRow(startX, baseY + 180.0f, rowW, "Hunger Limit", sim.glodKVal, 1, 1000, 5);
                ch |= DrawNumericRow(startX, baseY + 210.0f, rowW, "Starving!", sim.starvingKVal, 1, 1000, 5);
                ch |= DrawNumericRow(startX, baseY + 240.0f, rowW, "Fox Detection", sim.detekcjaKVal, 1, 200, 5);
                ch |= DrawNumericRow(startX, baseY + 270.0f, rowW, "Lifespan", sim.zycieKVal, 1, 1000, 10);
                if (ch) sim.applyKrolikParams();

                // Clear All Rabbits button - well above the bottom border
                if (DrawButton({ startX + 8.0f, baseY + 306.0f, rowW - 16.0f, 26.0f }, "Clear All Rabbits")) {
                    sim.krol->czysc();
                }
            }
            else if (sim.activeInformerTab == 2) { // Foxes
                DrawNumericRow(startX, baseY + 0.0f, rowW, "Spawn Count", sim.upDownIleL, 1, 999, 5);
                if (DrawButton({ startX + 8.0f, baseY + 28.0f, rowW - 16.0f, 26.0f }, "+ Spawn Foxes Now")) {
                    sim.generujLisy(sim.upDownIleL);
                }

                bool ch = false;
                ch |= DrawNumericRow(startX, baseY +  60.0f, rowW, "Speed (0.1x)", sim.vlVal, 1, 50, 1, "0.1x");
                ch |= DrawNumericRow(startX, baseY +  90.0f, rowW, "Metabolism", sim.metaLVal, 1, 50);
                ch |= DrawNumericRow(startX, baseY + 120.0f, rowW, "Nutritive Val", sim.wodzLVal, 1, 5000, 50);
                ch |= DrawNumericRow(startX, baseY + 150.0f, rowW, "Stomach Size", sim.zoladekLVal, 1, 5000, 50);
                ch |= DrawNumericRow(startX, baseY + 180.0f, rowW, "Hunger Limit", sim.glodLVal, 1, 5000, 50);
                ch |= DrawNumericRow(startX, baseY + 210.0f, rowW, "Lifespan", sim.zycieLVal, 1, 5000, 50);
                ch |= DrawNumericRow(startX, baseY + 240.0f, rowW, "Maturity Age", sim.dojrzaloscLVal, 1, 1000, 5);
                ch |= DrawNumericRow(startX, baseY + 270.0f, rowW, "Gestation", sim.ciazaLVal, 1, 1000, 5);
                if (ch) sim.applyLisParams();

                // Clear All Foxes button - well above the bottom border
                if (DrawButton({ startX + 8.0f, baseY + 306.0f, rowW - 16.0f, 26.0f }, "Clear All Foxes")) {
                    sim.lis->czysc();
                }
            }
            else if (sim.activeInformerTab == 3) { // Stats
                char bKr[32], bLi[32], bZ1K[32], bZ2K[32], bZ3K[32], bZ1L[32], bZ2L[32], bTick[32];
                snprintf(bKr, sizeof(bKr), "%zu", sim.Ktab.size());
                snprintf(bLi, sizeof(bLi), "%zu", sim.Ltab.size());
                snprintf(bZ1K, sizeof(bZ1K), "%ld", sim.krol ? sim.krol->z1 : 0);
                snprintf(bZ2K, sizeof(bZ2K), "%ld", sim.krol ? sim.krol->z2 : 0);
                snprintf(bZ3K, sizeof(bZ3K), "%ld", sim.lis ? sim.lis->z3 : 0);
                snprintf(bZ1L, sizeof(bZ1L), "%ld", sim.lis ? sim.lis->z1 : 0);
                snprintf(bZ2L, sizeof(bZ2L), "%ld", sim.lis ? sim.lis->z2 : 0);
                snprintf(bTick, sizeof(bTick), "%d", sim.plus);

                DrawReadOnlyEditRow(startX, baseY +   0.0f, rowW, "Alive Rabbits", bKr);
                DrawReadOnlyEditRow(startX, baseY +  28.0f, rowW, "Alive Foxes", bLi);
                DrawReadOnlyEditRow(startX, baseY +  56.0f, rowW, "Rabbit Starved", bZ1K);
                DrawReadOnlyEditRow(startX, baseY +  84.0f, rowW, "Rabbit Old Age", bZ2K);
                DrawReadOnlyEditRow(startX, baseY + 112.0f, rowW, "Rabbit Hunted", bZ3K);
                DrawReadOnlyEditRow(startX, baseY + 140.0f, rowW, "Fox Starved", bZ1L);
                DrawReadOnlyEditRow(startX, baseY + 168.0f, rowW, "Fox Old Age", bZ2L);
                DrawReadOnlyEditRow(startX, baseY + 196.0f, rowW, "Simulation Tick", bTick);
            }
            else if (sim.activeInformerTab == 4) { // My Rabbit (Individual Tracking & Control)
                int maxK = (sim.Ktab.size() > 0) ? ((int)sim.Ktab.size() - 1) : 0;
                DrawNumericRow(startX, baseY + 0.0f, rowW, "Rabbit #", sim.selectedKrolikIdx, 0, maxK);

                if (sim.selectedKrolikIdx >= 0 && sim.selectedKrolikIdx < (int)sim.Ktab.size()) {
                    auto& k = sim.Ktab[sim.selectedKrolikIdx];
                    const char* stStr = "unknown";
                    switch (k.status) {
                        case 3: stStr = "Mating search"; break;
                        case 2: stStr = "Hungry"; break;
                        case 1: stStr = "Fleeing fox!"; break;
                        case 0: stStr = "STARVING!"; break;
                    }
                    char bWiek[32], bZol[32], bCiaz[32], bWielk[32];
                    snprintf(bWiek, sizeof(bWiek), "%d / %d", k.wiek, sim.zycieKVal);
                    snprintf(bZol, sizeof(bZol), "%.1f", k.zoladek);
                    if (k.ciaza >= 0) snprintf(bCiaz, sizeof(bCiaz), "%d", k.ciaza);
                    else snprintf(bCiaz, sizeof(bCiaz), "---");
                    snprintf(bWielk, sizeof(bWielk), "%.2f", k.wielkosc);

                    DrawReadOnlyEditRow(startX, baseY +  28.0f, rowW, "Status", stStr);
                    DrawReadOnlyEditRow(startX, baseY +  56.0f, rowW, "Gender", k.plec ? "Male (XY)" : "Female (XX)");
                    DrawReadOnlyEditRow(startX, baseY +  84.0f, rowW, "Age / Max", bWiek);
                    DrawReadOnlyEditRow(startX, baseY + 112.0f, rowW, "Stomach", bZol);
                    DrawReadOnlyEditRow(startX, baseY + 140.0f, rowW, "Gestation", bCiaz);
                    DrawReadOnlyEditRow(startX, baseY + 168.0f, rowW, "Body Size", bWielk);

                    if (DrawButton({ startX + 8.0f, baseY + 200.0f, rowW - 16.0f, 26.0f }, "Feed Rabbit (Max Energy)")) {
                        k.zoladek = (float)sim.zoladekKVal;
                    }
                    if (DrawButton({ startX + 8.0f, baseY + 232.0f, rowW - 16.0f, 24.0f }, "Remove Selected Rabbit")) {
                        sim.Ktab.erase(sim.Ktab.begin() + sim.selectedKrolikIdx);
                        if (sim.selectedKrolikIdx >= (int)sim.Ktab.size() && sim.selectedKrolikIdx > 0) {
                            sim.selectedKrolikIdx--;
                        }
                    }
                } else {
                    DrawLabel(startX + 10.0f, baseY + 36.0f, "No rabbit selected.\nClick any rabbit on map\nto inspect and manage.", 10, CLR_TEXT);
                    if (DrawButton({ startX + 16.0f, baseY + 100.0f, rowW - 32.0f, 30.0f }, "+ Spawn 50 Rabbits")) {
                        sim.generujKroliki(50);
                    }
                }
            }
            else if (sim.activeInformerTab == 5) { // My Fox (Individual Tracking & Control)
                int maxL = (sim.Ltab.size() > 0) ? ((int)sim.Ltab.size() - 1) : 0;
                DrawNumericRow(startX, baseY + 0.0f, rowW, "Fox #", sim.selectedLisIdx, 0, maxL);

                if (sim.selectedLisIdx >= 0 && sim.selectedLisIdx < (int)sim.Ltab.size()) {
                    auto& l = sim.Ltab[sim.selectedLisIdx];
                    const char* stStr = "unknown";
                    switch (l.status) {
                        case 2: stStr = "Mating search"; break;
                        case 1: stStr = "Hunting rabbit"; break;
                        case 0: stStr = "Prowling"; break;
                    }
                    char bWiek[32], bZol[32], bCiaz[32], bWielk[32];
                    snprintf(bWiek, sizeof(bWiek), "%d / %d", l.wiek, sim.zycieLVal);
                    snprintf(bZol, sizeof(bZol), "%.1f", l.zoladek);
                    if (l.ciaza >= 0) snprintf(bCiaz, sizeof(bCiaz), "%d", l.ciaza);
                    else snprintf(bCiaz, sizeof(bCiaz), "---");
                    snprintf(bWielk, sizeof(bWielk), "%.2f", l.wielkosc);

                    DrawReadOnlyEditRow(startX, baseY +  28.0f, rowW, "Status", stStr);
                    DrawReadOnlyEditRow(startX, baseY +  56.0f, rowW, "Gender", l.plec ? "Male (XY)" : "Female (XX)");
                    DrawReadOnlyEditRow(startX, baseY +  84.0f, rowW, "Age / Max", bWiek);
                    DrawReadOnlyEditRow(startX, baseY + 112.0f, rowW, "Stomach", bZol);
                    DrawReadOnlyEditRow(startX, baseY + 140.0f, rowW, "Gestation", bCiaz);
                    DrawReadOnlyEditRow(startX, baseY + 168.0f, rowW, "Body Size", bWielk);

                    if (DrawButton({ startX + 8.0f, baseY + 200.0f, rowW - 16.0f, 26.0f }, "Feed Fox (Max Energy)")) {
                        l.zoladek = (float)sim.zoladekLVal;
                    }
                    if (DrawButton({ startX + 8.0f, baseY + 232.0f, rowW - 16.0f, 24.0f }, "Remove Selected Fox")) {
                        sim.Ltab.erase(sim.Ltab.begin() + sim.selectedLisIdx);
                        if (sim.selectedLisIdx >= (int)sim.Ltab.size() && sim.selectedLisIdx > 0) {
                            sim.selectedLisIdx--;
                        }
                    }
                } else {
                    DrawLabel(startX + 10.0f, baseY + 36.0f, "No fox selected.\nClick any fox on map\nto inspect and manage.", 10, CLR_TEXT);
                    if (DrawButton({ startX + 16.0f, baseY + 100.0f, rowW - 32.0f, 30.0f }, "+ Spawn 10 Foxes")) {
                        sim.generujLisy(10);
                    }
                }
            }
            else if (sim.activeInformerTab == 6) { // Evolution
                float sWielkK = 0, sGlodK = 0, sStarvK = 0;
                if (!sim.Ktab.empty()) {
                    for (const auto& k : sim.Ktab) {
                        sWielkK += k.wielkosc;
                        sGlodK  += k.glod;
                        sStarvK += k.starving;
                    }
                    sWielkK /= sim.Ktab.size();
                    sGlodK  /= sim.Ktab.size();
                    sStarvK /= sim.Ktab.size();
                }

                float sWielkL = 0, sGlodL = 0;
                if (!sim.Ltab.empty()) {
                    for (const auto& l : sim.Ltab) {
                        sWielkL += l.wielkosc;
                        sGlodL  += l.glod;
                    }
                    sWielkL /= sim.Ltab.size();
                    sGlodL  /= sim.Ltab.size();
                }

                char bWK[32], bGK[32], bSK[32], bWL[32], bGL[32];
                snprintf(bWK, sizeof(bWK), "%.2f", sWielkK);
                snprintf(bGK, sizeof(bGK), "%.1f", sGlodK);
                snprintf(bSK, sizeof(bSK), "%.1f", sStarvK);
                snprintf(bWL, sizeof(bWL), "%.2f", sWielkL);
                snprintf(bGL, sizeof(bGL), "%.1f", sGlodL);

                DrawLabel(startX, baseY + 2.0f, "Rabbit Population Averages:", 10, CLR_NAVY);
                DrawReadOnlyEditRow(startX, baseY + 24.0f, rowW, "Avg Body Size", bWK);
                DrawReadOnlyEditRow(startX, baseY + 52.0f, rowW, "Avg Hunger", bGK);
                DrawReadOnlyEditRow(startX, baseY + 80.0f, rowW, "Avg STARVING!", bSK);

                DrawLabel(startX, baseY + 116.0f, "Fox Population Averages:", 10, CLR_NAVY);
                DrawReadOnlyEditRow(startX, baseY + 138.0f, rowW, "Avg Body Size", bWL);
                DrawReadOnlyEditRow(startX, baseY + 166.0f, rowW, "Avg Hunger", bGL);
            }
        }

        // -------------------------------------------------------------------------
        // 3. Right Bottom Navigation and Screen Control Panel
        // -------------------------------------------------------------------------
        const float navY = panelY + panelH + 8.0f; // 606px
        const float navH = mapTop + mapH - navY;   // 88px
        Rectangle bottomPanelRect = { panelX, navY, panelW, navH };
        DrawGroupBox(bottomPanelRect, "Navigation / Screen");

        if (sim.poziom == 0) {
            DrawButton({ panelX + 10.0f, navY + 20.0f, 90.0f, 28.0f }, "<< Setup", false);

            if (DrawButton({ panelX + 106.0f, navY + 20.0f, panelW - 116.0f, 28.0f }, "Start Simulation >>", true, CLR_TEXT)) {
                sim.butOkClick();
            }
        } else {
            if (DrawButton({ panelX + 10.0f, navY + 20.0f, 90.0f, 28.0f }, "<< Island", true)) {
                sim.butPowrotClick();
            }

            const char* pauseLabel = sim.running ? "Pause (Space)" : "Resume (Space)";
            Color pauseCol = sim.running ? CLR_TEXT : RED;
            if (DrawButton({ panelX + 106.0f, navY + 20.0f, panelW - 116.0f, 28.0f }, pauseLabel, true, pauseCol)) {
                sim.running = !sim.running;
            }
        }

        // Fullscreen toggle button
        const char* fsText = IsWindowFullscreen() ? "Windowed Mode (F11)" : "Fullscreen (F11)";
        if (DrawButton({ panelX + 10.0f, navY + 54.0f, panelW - 20.0f, 26.0f }, fsText)) {
            ToggleFullscreen();
        }

        // -------------------------------------------------------------------------
        // 4. Bottom Full-Width Status Bar & Speed Control
        // -------------------------------------------------------------------------
        Simulation::IslandStats stats = sim.getIslandStats();

        const float barY = mapTop + mapH + 8.0f; // 702px
        const float barH = (float)VIRTUAL_H - barY - 8.0f; // 38px
        const float barX = 14.0f;

        // Status Panel 1: Alive Rabbits
        char statK[32];
        snprintf(statK, sizeof(statK), "Rabbits: %zu", sim.Ktab.size());
        Rectangle statBoxK = { barX, barY, 120.0f, barH };
        DrawSunkenBox(statBoxK, CLR_BG);
        DrawTextBold(statK, statBoxK.x + 6.0f, statBoxK.y + (barH - (float)ClassicUI::GetBaseFontSize()) * 0.5f, 10, CLR_NAVY);

        // Status Panel 2: Alive Foxes
        char statL[32];
        snprintf(statL, sizeof(statL), "Foxes: %zu", sim.Ltab.size());
        Rectangle statBoxL = { barX + 126.0f, barY, 110.0f, barH };
        DrawSunkenBox(statBoxL, CLR_BG);
        DrawTextBold(statL, statBoxL.x + 6.0f, statBoxL.y + (barH - (float)ClassicUI::GetBaseFontSize()) * 0.5f, 10, RED);

        // Status Panel 3: Grass Biomass / Coverage
        char statGrass[48];
        snprintf(statGrass, sizeof(statGrass), "Grass: %.1f%%", stats.grassPercent);
        Rectangle statBoxG = { barX + 242.0f, barY, 130.0f, barH };
        DrawSunkenBox(statBoxG, CLR_BG);
        DrawTextBold(statGrass, statBoxG.x + 6.0f, statBoxG.y + (barH - (float)ClassicUI::GetBaseFontSize()) * 0.5f, 10, DARKGREEN);

        // Status Panel 4: Simulation Tick
        char statTick[32];
        snprintf(statTick, sizeof(statTick), "Tick: %d", sim.plus);
        Rectangle statBoxT = { barX + 378.0f, barY, 110.0f, barH };
        DrawSunkenBox(statBoxT, CLR_BG);
        DrawTextBold(statTick, statBoxT.x + 6.0f, statBoxT.y + (barH - (float)ClassicUI::GetBaseFontSize()) * 0.5f, 10, CLR_TEXT);

        // Status Panel 5: Speed Slider / Control Bar (spans from x=494 to 1266)
        float spdPanelX = barX + 494.0f; // 508px
        float spdPanelW = (float)VIRTUAL_W - barX - spdPanelX; // 758px
        Rectangle speedPanel = { spdPanelX, barY, spdPanelW, barH };
        DrawSunkenBox(speedPanel, CLR_BG);

        float curX = spdPanelX + 12.0f;
        float midY = barY + (barH - (float)ClassicUI::GetBaseFontSize()) * 0.5f;
        float btnY = barY + 6.0f;
        float btnH = barH - 12.0f; // 26px

        DrawTextBold("Speed:", curX, midY, 10, CLR_NAVY);
        curX += 58.0f;

        // Slower button [-]
        if (DrawButton({ curX, btnY, 26.0f, btnH }, "-")) {
            if (speedMultiplier > 1.0f) speedMultiplier -= 1.0f;
            else if (speedMultiplier > 0.5f) speedMultiplier = 0.5f;
            else if (speedMultiplier > 0.25f) speedMultiplier = 0.25f;
        }
        curX += 30.0f;

        // Current speed readout
        char spdBuf[16];
        if (speedMultiplier < 1.0f) snprintf(spdBuf, sizeof(spdBuf), "%.2fx", speedMultiplier);
        else snprintf(spdBuf, sizeof(spdBuf), "%.0fx", speedMultiplier);

        Rectangle spdValBox = { curX, btnY, 54.0f, btnH };
        DrawSunkenBox(spdValBox, CLR_YELLOW_BG);
        int spdTw = MeasureTextBold(spdBuf, 10);
        DrawTextBold(spdBuf, spdValBox.x + (spdValBox.width - spdTw) * 0.5f, midY, 10, CLR_TEXT);
        curX += 58.0f;

        // Faster button [+]
        if (DrawButton({ curX, btnY, 26.0f, btnH }, "+")) {
            if (speedMultiplier < 0.5f) speedMultiplier = 0.5f;
            else if (speedMultiplier < 1.0f) speedMultiplier = 1.0f;
            else if (speedMultiplier < 10.0f) speedMultiplier += 1.0f;
        }
        curX += 34.0f;

        // Preset speed buttons (every single button fits comfortably!)
        if (DrawButton({ curX, btnY, 44.0f, btnH }, "0.5x", true, (speedMultiplier == 0.5f) ? RED : CLR_TEXT)) {
            speedMultiplier = 0.5f;
        }
        curX += 48.0f;

        if (DrawButton({ curX, btnY, 36.0f, btnH }, "1x", true, (speedMultiplier == 1.0f) ? RED : CLR_TEXT)) {
            speedMultiplier = 1.0f;
        }
        curX += 40.0f;

        if (DrawButton({ curX, btnY, 36.0f, btnH }, "2x", true, (speedMultiplier == 2.0f) ? RED : CLR_TEXT)) {
            speedMultiplier = 2.0f;
        }
        curX += 40.0f;

        if (DrawButton({ curX, btnY, 36.0f, btnH }, "5x", true, (speedMultiplier == 5.0f) ? RED : CLR_TEXT)) {
            speedMultiplier = 5.0f;
        }
        curX += 40.0f;

        if (DrawButton({ curX, btnY, 44.0f, btnH }, "10x", true, (speedMultiplier == 10.0f) ? RED : CLR_TEXT)) {
            speedMultiplier = 10.0f;
        }

        EndTextureMode();

        // =========================================================================
        // PRESENTATION TO WINDOW WITH ASPECT RATIO PRESERVATION (LETTERBOX)
        // =========================================================================
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
        Rectangle destRec   = { offsetX, offsetY, (float)VIRTUAL_W * scale, (float)VIRTUAL_H * scale };
        Vector2 origin      = { 0.0f, 0.0f };

        DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);

        EndDrawing();
    }

    // Resource cleanup
    ClassicUI::Shutdown();
    UnloadTexture(islandTexture);
    if (texKrolik.id != 0)  UnloadTexture(texKrolik);
    if (texLis.id != 0)     UnloadTexture(texLis);
    if (texWybrany.id != 0) UnloadTexture(texWybrany);
    UnloadRenderTexture(target);

    CloseWindow();
    return 0;
}
