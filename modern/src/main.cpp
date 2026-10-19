#include "raylib.h"
#include "Simulation.h"
#include "ClassicUI.h"
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

using namespace ClassicUI;

// Virtual canvas dimensions matching the authentic Borland C++Builder 6 window
static const int VIRTUAL_W = 752;
static const int VIRTUAL_H = 418;

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
    // Initial window size (1.6x logical resolution for crisp display on high-DPI monitors)
    const int startWindowW = 1200;
    const int startWindowH = 668;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(startWindowW, startWindowH, "Australia 1859 Sim - Island Ecosystem Simulator (Dawid Domagala)");
    SetWindowMinSize(752, 418);
    SetTargetFPS(60);

    // RenderTexture for fixed virtual resolution and pixel-perfect letterbox scaling
    RenderTexture2D target = LoadRenderTexture(VIRTUAL_W, VIRTUAL_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

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
        if (IsKeyPressed(KEY_ONE))   sim.simSpeed = 1;
        if (IsKeyPressed(KEY_TWO))   sim.simSpeed = 2;
        if (IsKeyPressed(KEY_THREE)) sim.simSpeed = 5;
        if (IsKeyPressed(KEY_FOUR))  sim.simSpeed = 10;

        // Step simulation logic
        sim.update();

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

        // Select rabbit / fox by clicking on the 500x400 map
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && sim.poziom == 1) {
            int mx = (int)vMouse.x - 8;
            int my = (int)vMouse.y - 8;
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
        // DRAW TO VIRTUAL RENDER TARGET (VIRTUAL_W x VIRTUAL_H)
        // =========================================================================
        BeginTextureMode(target);
        ClearBackground(CLR_BG);

        // 1. 500x400 Island map on left in a 3D sunken border
        Rectangle mapBorder = { 6, 6, 504, 404 };
        DrawSunkenBox(mapBorder, BLACK);
        DrawTexture(islandTexture, 8, 8, WHITE);

        // Draw rabbits
        for (const auto& k : sim.Ktab) {
            if (texKrolik.id != 0) {
                DrawTexture(texKrolik, k.x - 2 + 8, k.y - 2 + 8, WHITE);
            } else {
                DrawRectangle(k.x - 1 + 8, k.y - 1 + 8, 3, 3, WHITE);
            }
        }

        // Draw foxes
        for (const auto& l : sim.Ltab) {
            if (texLis.id != 0) {
                DrawTexture(texLis, l.x - 2 + 8, l.y - 2 + 8, WHITE);
            } else {
                DrawRectangle(l.x - 2 + 8, l.y - 2 + 8, 4, 4, RED);
            }
        }

        // Highlight selected animal
        if (sim.poziom == 1) {
            if (sim.activeInformerTab == 4 && sim.selectedKrolikIdx >= 0 && sim.selectedKrolikIdx < (int)sim.Ktab.size()) {
                const auto& selK = sim.Ktab[sim.selectedKrolikIdx];
                if (texWybrany.id != 0) {
                    DrawTexture(texWybrany, selK.x - 3 + 8, selK.y - 3 + 8, WHITE);
                } else {
                    DrawRectangleLines(selK.x - 4 + 8, selK.y - 4 + 8, 9, 9, YELLOW);
                }
            } else if (sim.activeInformerTab == 5 && sim.selectedLisIdx >= 0 && sim.selectedLisIdx < (int)sim.Ltab.size()) {
                const auto& selL = sim.Ltab[sim.selectedLisIdx];
                if (texWybrany.id != 0) {
                    DrawTexture(texWybrany, selL.x - 3 + 8, selL.y - 3 + 8, WHITE);
                } else {
                    DrawRectangleLines(selL.x - 4 + 8, selL.y - 4 + 8, 9, 9, YELLOW);
                }
            }
        }

        // 2. Control Panel on right
        const float panelX = 516.0f;
        const float panelY = 8.0f;
        const float panelW = 228.0f;
        const float panelH = 286.0f;
        Rectangle groupBoxRect = { panelX, panelY, panelW, panelH };

        // -------------------------------------------------------------------------
        // PHASE 1: Island Generator
        // -------------------------------------------------------------------------
        if (sim.poziom == 0) {
            DrawGroupBox(groupBoxRect, "Island Generator ver. 1.4");

            const char* godTabs[] = { "Shape", "Bays", "Adjust", "Terrain" };
            Rectangle tabRect = { panelX + 6.0f, panelY + 18.0f, panelW - 12.0f, 20.0f };
            sim.activeGodTab = DrawTabs(tabRect, godTabs, 4, sim.activeGodTab);

            float rowW = panelW - 24.0f;
            float startX = panelX + 12.0f;

            if (sim.activeGodTab == 0) { // Shape
                DrawLabel(startX + 6.0f, panelY + 54.0f, "Shape Amplitude:", 10, CLR_NAVY);
                Rectangle rectUp = { startX + 110.0f, panelY + 50.0f, 60.0f, 20.0f };
                DrawUpDown(rectUp, sim.amplitude, 1, 1000, 5);

                if (DrawButton({ startX + 16.0f, panelY + 90.0f, rowW - 32.0f, 44.0f }, "Generate Island")) {
                    sim.generujWyspe(sim.amplitude);
                }

                DrawLabel(startX + 4.0f, panelY + 155.0f, "Set shape amplitude and click\n'Generate Island' to forge\na new island boundary.\n\nThen use Bays & Adjust to sculpt.", 10, CLR_TEXT);
            }
            else if (sim.activeGodTab == 1) { // Bays
                DrawUpDownRow(startX, panelY + 48.0f, rowW, "Bay Count", sim.upDownLzatok, 1, 99);
                DrawUpDownRow(startX, panelY + 74.0f, rowW, "Bay Size", sim.upDownWZatok, 1, 1000, 5);
                DrawUpDownRow(startX, panelY + 100.0f, rowW, "Irregularity", sim.upDownRZatok, 0, 999, 5);

                if (DrawButton({ startX + 10.0f, panelY + 134.0f, rowW - 20.0f, 32.0f }, "Carve Deep Bays")) {
                    sim.dodajZatoki(sim.upDownLzatok, sim.upDownWZatok, sim.upDownRZatok);
                }
                if (DrawButton({ startX + 10.0f, panelY + 176.0f, rowW - 20.0f, 32.0f }, "Carve Coastal Bays")) {
                    sim.dodajZatokiPlaza(sim.upDownLzatok, sim.upDownWZatok, sim.upDownRZatok);
                }
            }
            else if (sim.activeGodTab == 2) { // Adjust
                DrawLabel(startX + 14.0f, panelY + 48.0f, "Expand (+)", 10, CLR_NAVY);
                if (DrawButton({ startX + 10.0f, panelY + 64.0f, 64.0f, 44.0f }, "+")) {
                    sim.zwiekszLad();
                }

                DrawLabel(startX + 114.0f, panelY + 48.0f, "Shrink (-)", 10, CLR_NAVY);
                if (DrawButton({ startX + 110.0f, panelY + 64.0f, 64.0f, 44.0f }, "-")) {
                    sim.zmniejszLad();
                }

                DrawUpDownRow(startX, panelY + 126.0f, rowW, "Smoothing Pass", sim.upDownGladz, 1, 20);
                if (DrawButton({ startX + 10.0f, panelY + 160.0f, rowW - 20.0f, 32.0f }, "Smooth Coastline")) {
                    sim.wygladz(sim.upDownGladz);
                }
            }
            else if (sim.activeGodTab == 3) { // Terrain
                if (DrawUpDownRow(startX, panelY + 48.0f, rowW, "Beach Width", sim.upDownPlaza, 0, 200, 5) ||
                    DrawUpDownRow(startX, panelY + 72.0f, rowW, "Grass Zone", sim.upDownTrawa, 0, 200, 5) ||
                    DrawUpDownRow(startX, panelY + 96.0f, rowW, "Snow Zone", sim.upDownSnieg, 0, 200, 5)) {
                    sim.pallad();
                }

                DrawUpDownRow(startX, panelY + 124.0f, rowW, "Noise Grain", sim.upDownZiarno, 0, 16);

                if (DrawButton({ startX + 10.0f, panelY + 154.0f, rowW - 20.0f, 28.0f }, "Add Terrain Noise")) {
                    sim.dodajZiarno(sim.upDownZiarno);
                }
                if (DrawButton({ startX + 10.0f, panelY + 190.0f, rowW - 20.0f, 28.0f }, "Apply Palette")) {
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

            // Two-row MultiLine TabControl
            const char* tabsRow1[] = { "Grass", "Rabbits", "Foxes", "Stats" };
            const char* tabsRow2[] = { "My Rabbit", "My Fox", "Evolution" };

            Rectangle tabR1 = { panelX + 6.0f, panelY + 16.0f, panelW - 12.0f, 18.0f };
            Rectangle tabR2 = { panelX + 6.0f, panelY + 34.0f, panelW - 12.0f, 18.0f };

            int curR1 = (sim.activeInformerTab < 4) ? sim.activeInformerTab : -1;
            int selR1 = DrawTabs(tabR1, tabsRow1, 4, curR1);
            if (selR1 != curR1 && selR1 >= 0) sim.activeInformerTab = selR1;

            int curR2 = (sim.activeInformerTab >= 4) ? (sim.activeInformerTab - 4) : -1;
            int selR2 = DrawTabs(tabR2, tabsRow2, 3, curR2);
            if (selR2 != curR2 && selR2 >= 0) sim.activeInformerTab = selR2 + 4;

            float baseY = panelY + 56.0f;

            if (sim.activeInformerTab == 0) { // Grass
                DrawUpDownRow(startX, baseY + 6.0f, rowW, "Vegetation Rate", sim.wegetacja, 1, 100);

                if (DrawButton({ startX + 10.0f, baseY + 40.0f, rowW - 20.0f, 32.0f }, "Lush Grass (Max)")) {
                    sim.maxTrawa();
                }
                if (DrawButton({ startX + 10.0f, baseY + 82.0f, rowW - 20.0f, 32.0f }, "Reset Grass Level")) {
                    sim.resetTrawy();
                }
                if (DrawButton({ startX + 10.0f, baseY + 124.0f, rowW - 20.0f, 32.0f }, "Mow Grass (Min)")) {
                    sim.minTrawa();
                }

                DrawLabel(startX + 8.0f, baseY + 172.0f, "Lower vegetation rate = faster\ngrass growth across the island.", 10, CLR_TEXT);
            }
            else if (sim.activeInformerTab == 1) { // Rabbits
                // Spawner section directly accessible
                DrawUpDownRow(startX, baseY + 0.0f, rowW, "Spawn Count", sim.upDownIleK, 1, 999, 10);
                if (DrawButton({ startX + 8.0f, baseY + 23.0f, rowW - 16.0f, 22.0f }, "+ Spawn Rabbits Now")) {
                    sim.generujKroliki(sim.upDownIleK);
                }

                // Genetic / metabolic parameters
                bool ch = false;
                ch |= DrawUpDownRow(startX, baseY +  50.0f, rowW, "Speed (0.1x)", sim.vkVal, 1, 50, 1, "0.1x");
                ch |= DrawUpDownRow(startX, baseY +  71.0f, rowW, "Metabolism", sim.metaKVal, 1, 50);
                ch |= DrawUpDownRow(startX, baseY +  92.0f, rowW, "Grass Bite", sim.kesKVal, 1, 255);
                ch |= DrawUpDownRow(startX, baseY + 113.0f, rowW, "Stomach Size", sim.zoladekKVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 134.0f, rowW, "Hunger Limit", sim.glodKVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 155.0f, rowW, "Starving!", sim.starvingKVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 176.0f, rowW, "Fox Detection", sim.detekcjaKVal, 1, 200, 5);
                ch |= DrawUpDownRow(startX, baseY + 197.0f, rowW, "Lifespan", sim.zycieKVal, 1, 1000, 10);
                if (ch) sim.applyKrolikParams();

                if (DrawButton({ startX + 8.0f, baseY + 220.0f, rowW - 16.0f, 18.0f }, "Clear All Rabbits")) {
                    sim.krol->czysc();
                }
            }
            else if (sim.activeInformerTab == 2) { // Foxes
                // Spawner section directly accessible
                DrawUpDownRow(startX, baseY + 0.0f, rowW, "Spawn Count", sim.upDownIleL, 1, 999, 5);
                if (DrawButton({ startX + 8.0f, baseY + 23.0f, rowW - 16.0f, 22.0f }, "+ Spawn Foxes Now")) {
                    sim.generujLisy(sim.upDownIleL);
                }

                // Genetic / metabolic parameters
                bool ch = false;
                ch |= DrawUpDownRow(startX, baseY +  50.0f, rowW, "Speed (0.1x)", sim.vlVal, 1, 50, 1, "0.1x");
                ch |= DrawUpDownRow(startX, baseY +  71.0f, rowW, "Metabolism", sim.metaLVal, 1, 50);
                ch |= DrawUpDownRow(startX, baseY +  92.0f, rowW, "Nutritive Val", sim.wodzLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY + 113.0f, rowW, "Stomach Size", sim.zoladekLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY + 134.0f, rowW, "Hunger Limit", sim.glodLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY + 155.0f, rowW, "Lifespan", sim.zycieLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY + 176.0f, rowW, "Maturity Age", sim.dojrzaloscLVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 197.0f, rowW, "Gestation", sim.ciazaLVal, 1, 1000, 5);
                if (ch) sim.applyLisParams();

                if (DrawButton({ startX + 8.0f, baseY + 220.0f, rowW - 16.0f, 18.0f }, "Clear All Foxes")) {
                    sim.lis->czysc();
                }
            }
            else if (sim.activeInformerTab == 3) { // Stats
                char bKr[32], bLi[32], bZ1K[32], bZ2K[32], bZ3K[32], bZ1L[32], bZ2L[32], bTick[32];
                snprintf(bKr, sizeof(bKr), "%zu", sim.Ktab.size());
                snprintf(bLi, sizeof(bLi), "%zu", sim.Ltab.size());
                snprintf(bZ1K, sizeof(bZ1K), "%d", sim.krol ? sim.krol->z1 : 0);
                snprintf(bZ2K, sizeof(bZ2K), "%d", sim.krol ? sim.krol->z2 : 0);
                snprintf(bZ3K, sizeof(bZ3K), "%d", sim.lis ? sim.lis->z3 : 0);
                snprintf(bZ1L, sizeof(bZ1L), "%d", sim.lis ? sim.lis->z1 : 0);
                snprintf(bZ2L, sizeof(bZ2L), "%d", sim.lis ? sim.lis->z2 : 0);
                snprintf(bTick, sizeof(bTick), "%d", sim.plus);

                DrawReadOnlyEditRow(startX, baseY +   0.0f, rowW, "Alive Rabbits", bKr);
                DrawReadOnlyEditRow(startX, baseY +  24.0f, rowW, "Alive Foxes", bLi);
                DrawReadOnlyEditRow(startX, baseY +  48.0f, rowW, "Rabbit Starved", bZ1K);
                DrawReadOnlyEditRow(startX, baseY +  72.0f, rowW, "Rabbit Old Age", bZ2K);
                DrawReadOnlyEditRow(startX, baseY +  96.0f, rowW, "Rabbit Hunted", bZ3K);
                DrawReadOnlyEditRow(startX, baseY + 120.0f, rowW, "Fox Starved", bZ1L);
                DrawReadOnlyEditRow(startX, baseY + 144.0f, rowW, "Fox Old Age", bZ2L);
                DrawReadOnlyEditRow(startX, baseY + 168.0f, rowW, "Simulation Tick", bTick);
            }
            else if (sim.activeInformerTab == 4) { // My Rabbit (Individual Tracking & Control)
                int maxK = (sim.Ktab.size() > 0) ? ((int)sim.Ktab.size() - 1) : 0;
                DrawUpDownRow(startX, baseY + 0.0f, rowW, "Rabbit #", sim.selectedKrolikIdx, 0, maxK);

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

                    DrawReadOnlyEditRow(startX, baseY +  24.0f, rowW, "Status", stStr);
                    DrawReadOnlyEditRow(startX, baseY +  48.0f, rowW, "Gender", k.plec ? "Male (XY)" : "Female (XX)");
                    DrawReadOnlyEditRow(startX, baseY +  72.0f, rowW, "Age / Max", bWiek);
                    DrawReadOnlyEditRow(startX, baseY +  96.0f, rowW, "Stomach", bZol);
                    DrawReadOnlyEditRow(startX, baseY + 120.0f, rowW, "Gestation", bCiaz);
                    DrawReadOnlyEditRow(startX, baseY + 144.0f, rowW, "Body Size", bWielk);

                    // Individual control buttons
                    if (DrawButton({ startX + 8.0f, baseY + 172.0f, rowW - 16.0f, 24.0f }, "Feed Rabbit (Max Energy)")) {
                        k.zoladek = (float)sim.zoladekKVal;
                    }
                    if (DrawButton({ startX + 8.0f, baseY + 200.0f, rowW - 16.0f, 22.0f }, "Remove Selected Rabbit")) {
                        sim.Ktab.erase(sim.Ktab.begin() + sim.selectedKrolikIdx);
                        if (sim.selectedKrolikIdx >= (int)sim.Ktab.size() && sim.selectedKrolikIdx > 0) {
                            sim.selectedKrolikIdx--;
                        }
                    }
                } else {
                    DrawLabel(startX + 10.0f, baseY + 36.0f, "No rabbit selected.\nClick any rabbit on map\nto inspect and manage.", 10, CLR_TEXT);
                    if (DrawButton({ startX + 16.0f, baseY + 100.0f, rowW - 32.0f, 32.0f }, "+ Spawn 50 Rabbits")) {
                        sim.generujKroliki(50);
                    }
                }
            }
            else if (sim.activeInformerTab == 5) { // My Fox (Individual Tracking & Control)
                int maxL = (sim.Ltab.size() > 0) ? ((int)sim.Ltab.size() - 1) : 0;
                DrawUpDownRow(startX, baseY + 0.0f, rowW, "Fox #", sim.selectedLisIdx, 0, maxL);

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

                    DrawReadOnlyEditRow(startX, baseY +  24.0f, rowW, "Status", stStr);
                    DrawReadOnlyEditRow(startX, baseY +  48.0f, rowW, "Gender", l.plec ? "Male (XY)" : "Female (XX)");
                    DrawReadOnlyEditRow(startX, baseY +  72.0f, rowW, "Age / Max", bWiek);
                    DrawReadOnlyEditRow(startX, baseY +  96.0f, rowW, "Stomach", bZol);
                    DrawReadOnlyEditRow(startX, baseY + 120.0f, rowW, "Gestation", bCiaz);
                    DrawReadOnlyEditRow(startX, baseY + 144.0f, rowW, "Body Size", bWielk);

                    // Individual control buttons
                    if (DrawButton({ startX + 8.0f, baseY + 172.0f, rowW - 16.0f, 24.0f }, "Feed Fox (Max Energy)")) {
                        l.zoladek = (float)sim.zoladekLVal;
                    }
                    if (DrawButton({ startX + 8.0f, baseY + 200.0f, rowW - 16.0f, 22.0f }, "Remove Selected Fox")) {
                        sim.Ltab.erase(sim.Ltab.begin() + sim.selectedLisIdx);
                        if (sim.selectedLisIdx >= (int)sim.Ltab.size() && sim.selectedLisIdx > 0) {
                            sim.selectedLisIdx--;
                        }
                    }
                } else {
                    DrawLabel(startX + 10.0f, baseY + 36.0f, "No fox selected.\nClick any fox on map\nto inspect and manage.", 10, CLR_TEXT);
                    if (DrawButton({ startX + 16.0f, baseY + 100.0f, rowW - 32.0f, 32.0f }, "+ Spawn 10 Foxes")) {
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
                DrawReadOnlyEditRow(startX, baseY + 18.0f, rowW, "Avg Body Size", bWK);
                DrawReadOnlyEditRow(startX, baseY + 42.0f, rowW, "Avg Hunger", bGK);
                DrawReadOnlyEditRow(startX, baseY + 66.0f, rowW, "Avg STARVING!", bSK);

                DrawLabel(startX, baseY + 96.0f, "Fox Population Averages:", 10, CLR_NAVY);
                DrawReadOnlyEditRow(startX, baseY + 112.0f, rowW, "Avg Body Size", bWL);
                DrawReadOnlyEditRow(startX, baseY + 136.0f, rowW, "Avg Hunger", bGL);
            }
        }

        // -------------------------------------------------------------------------
        // 3. Bottom Navigation and Screen Control Panel
        // -------------------------------------------------------------------------
        Rectangle bottomPanelRect = { panelX, panelY + panelH + 8.0f, panelW, 110.0f };
        DrawGroupBox(bottomPanelRect, "Navigation / Screen");

        if (sim.poziom == 0) {
            // In Phase 1 (Island Generator)
            DrawButton({ panelX + 8.0f, panelY + panelH + 24.0f, 68.0f, 40.0f }, "<< Setup", false);

            if (DrawButton({ panelX + 82.0f, panelY + panelH + 24.0f, panelW - 90.0f, 40.0f }, "Start Simulation >>", true, CLR_TEXT)) {
                sim.butOkClick();
            }
        } else {
            // In Phase 2 (Ecosystem Management & Simulation)
            if (DrawButton({ panelX + 8.0f, panelY + panelH + 24.0f, 68.0f, 40.0f }, "<< Island", true)) {
                sim.butPowrotClick();
            }

            const char* pauseLabel = sim.running ? "Pause (Space)" : "Resume (Space)";
            Color pauseCol = sim.running ? CLR_TEXT : RED;
            if (DrawButton({ panelX + 82.0f, panelY + panelH + 24.0f, panelW - 90.0f, 40.0f }, pauseLabel, true, pauseCol)) {
                sim.running = !sim.running;
            }
        }

        // Fullscreen toggle button
        const char* fsText = IsWindowFullscreen() ? "Windowed Mode (F11)" : "Fullscreen (F11)";
        if (DrawButton({ panelX + 8.0f, panelY + panelH + 68.0f, panelW - 16.0f, 34.0f }, fsText)) {
            ToggleFullscreen();
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
    UnloadTexture(islandTexture);
    if (texKrolik.id != 0)  UnloadTexture(texKrolik);
    if (texLis.id != 0)     UnloadTexture(texLis);
    if (texWybrany.id != 0) UnloadTexture(texWybrany);
    UnloadRenderTexture(target);

    CloseWindow();
    return 0;
}
