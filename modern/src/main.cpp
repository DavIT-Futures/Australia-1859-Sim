#include "raylib.h"
#include "Simulation.h"
#include "ClassicUI.h"
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

using namespace ClassicUI;

// Wymiary wirtualnego płótna odpowiadające oryginalnemu oknu Borland C++Builder 6
static const int VIRTUAL_W = 752;
static const int VIRTUAL_H = 418;

// Pomocnik do bezpiecznego ładowania tekstur BMP z przezroczystością koloru Magenta (clFuchsia 0xFF00FF)
static Texture2D LoadTransparentBMP(const char* path1, const char* path2) {
    Image img = { 0 };
    if (FileExists(path1)) {
        img = LoadImage(path1);
    } else if (FileExists(path2)) {
        img = LoadImage(path2);
    }

    if (img.data != nullptr) {
        // Zastąp kolor fioletowy/różowy (255, 0, 255) pełną przezroczystością
        ImageColorReplace(&img, Color{ 255, 0, 255, 255 }, BLANK);
        Texture2D tex = LoadTextureFromImage(img);
        UnloadImage(img);
        return tex;
    }
    return Texture2D{};
}

int main() {
    // Okno startowe w trybie okienkowym (1.6x skali dla ostrości na monitorach FHD/4K)
    const int startWindowW = 1200;
    const int startWindowH = 668;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(startWindowW, startWindowH, "Wyspa \"Spy VsSpy 1.3.\" - Autor: Dawid Domagala (Australia 1859 Sim)");
    SetWindowMinSize(752, 418);
    SetTargetFPS(60);

    // RenderTexture dla stałej rozdzielczości logicznej i idealnego skalowania Fullscreen
    RenderTexture2D target = LoadRenderTexture(VIRTUAL_W, VIRTUAL_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    Simulation sim;

    // Bufor RGBA dla mapy terenu 500x400
    std::vector<uint8_t> rgbaBuffer(Simulation::SZER * Simulation::WYS * 4, 255);
    Image islandImage = {
        rgbaBuffer.data(),
        Simulation::SZER,
        Simulation::WYS,
        1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture2D islandTexture = LoadTextureFromImage(islandImage);

    // Załaduj sprite'y zwierząt z oryginalnymi maskami
    Texture2D texKrolik  = LoadTransparentBMP("assets/krolik.bmp", "krolik.bmp");
    Texture2D texLis     = LoadTransparentBMP("assets/lis.bmp", "lis.bmp");
    Texture2D texWybrany = LoadTransparentBMP("assets/wybrany.bmp", "wybrany.bmp");

    while (!WindowShouldClose()) {
        // --- Obsługa pełnego ekranu (F11) ---
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        // Klawisze skrótów
        if (IsKeyPressed(KEY_SPACE)) {
            if (sim.poziom == 3) {
                sim.running = !sim.running;
            } else {
                sim.butOkClick();
            }
        }
        if (IsKeyPressed(KEY_ONE)) sim.simSpeed = 1;
        if (IsKeyPressed(KEY_TWO)) sim.simSpeed = 2;
        if (IsKeyPressed(KEY_THREE)) sim.simSpeed = 5;
        if (IsKeyPressed(KEY_FOUR)) sim.simSpeed = 10;

        // Aktualizacja symulacji
        sim.update();

        // Odświeżenie tekstury wyspy
        sim.renderToRGBA(rgbaBuffer.data());
        UpdateTexture(islandTexture, rgbaBuffer.data());

        // Obliczanie proporcji i wirtualnych współrzędnych myszy (Letterbox scaling)
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

        // Wybór królika / lisa kliknięciem na mapie (współrzędne mapy: x: 8..508, y: 8..408)
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int mx = (int)vMouse.x - 8;
            int my = (int)vMouse.y - 8;
            if (mx >= 0 && mx < Simulation::SZER && my >= 0 && my < Simulation::WYS) {
                // Szukaj najbliższego królika
                int bestK = -1;
                float bestDistK = 15.0f;
                for (size_t i = 0; i < sim.Ktab.size(); i++) {
                    float d = hypotf((float)(sim.Ktab[i].x - mx), (float)(sim.Ktab[i].y - my));
                    if (d < bestDistK) {
                        bestDistK = d;
                        bestK = (int)i;
                    }
                }
                // Szukaj najbliższego lisa
                int bestL = -1;
                float bestDistL = 15.0f;
                for (size_t i = 0; i < sim.Ltab.size(); i++) {
                    float d = hypotf((float)(sim.Ltab[i].x - mx), (float)(sim.Ltab[i].y - my));
                    if (d < bestDistL) {
                        bestDistL = d;
                        bestL = (int)i;
                    }
                }

                if (bestL >= 0 && bestDistL <= bestDistK) {
                    sim.selectedLisIdx = bestL;
                    sim.activeInformerTab = 5; // Tab "Mój lis"
                } else if (bestK >= 0) {
                    sim.selectedKrolikIdx = bestK;
                    sim.activeInformerTab = 4; // Tab "Mój królik"
                }
            }
        }

        // =========================================================================
        // RYSOWANIE DO WIRTUALNEGO RENDER TARGETU (VIRTUAL_W x VIRTUAL_H)
        // =========================================================================
        BeginTextureMode(target);
        ClearBackground(CLR_BG);

        // 1. Mapa 500x400 po lewej stronie w ramce 3D sunken
        Rectangle mapBorder = { 6, 6, 504, 404 };
        DrawSunkenBox(mapBorder, BLACK);
        DrawTexture(islandTexture, 8, 8, WHITE);

        // Rysowanie królików na mapie
        for (const auto& k : sim.Ktab) {
            if (texKrolik.id != 0) {
                DrawTexture(texKrolik, k.x - 2 + 8, k.y - 2 + 8, WHITE);
            } else {
                DrawRectangle(k.x - 1 + 8, k.y - 1 + 8, 3, 3, WHITE);
            }
        }

        // Rysowanie lisów na mapie
        for (const auto& l : sim.Ltab) {
            if (texLis.id != 0) {
                DrawTexture(texLis, l.x - 2 + 8, l.y - 2 + 8, WHITE);
            } else {
                DrawRectangle(l.x - 2 + 8, l.y - 2 + 8, 4, 4, RED);
            }
        }

        // Wskaźnik wybranego osobnika (wybrany.bmp)
        if (sim.poziom == 3) {
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

        // 2. Prawy panel sterowania (GroupBox zależny od sim.poziom)
        const float panelX = 516.0f;
        const float panelY = 8.0f;
        const float panelW = 228.0f;
        const float panelH = 286.0f;
        Rectangle groupBoxRect = { panelX, panelY, panelW, panelH };

        // -------------------------------------------------------------------------
        // POZIOM 0: Generator "Bóg ver. 1.3.12"
        // -------------------------------------------------------------------------
        if (sim.poziom == 0) {
            DrawGroupBox(groupBoxRect, "Generator \"Bóg ver. 1.3.12\"");

            const char* godTabs[] = { "Kształt", "Zatoki", "Korekta", "Wnętrze" };
            Rectangle tabRect = { panelX + 6.0f, panelY + 18.0f, panelW - 12.0f, 20.0f };
            sim.activeGodTab = DrawTabs(tabRect, godTabs, 4, sim.activeGodTab);

            float rowW = panelW - 24.0f;
            float startX = panelX + 12.0f;

            if (sim.activeGodTab == 0) { // Kształt
                DrawLabel(startX + 10.0f, panelY + 54.0f, "Kształt:", 12, CLR_NAVY);
                Rectangle rectUp = { startX + 90.0f, panelY + 52.0f, 60.0f, 20.0f };
                DrawUpDown(rectUp, sim.amplitude, 1, 1000, 5);

                if (DrawButton({ startX + 16.0f, panelY + 90.0f, rowW - 32.0f, 44.0f }, "Generuj")) {
                    sim.generujWyspe(sim.amplitude);
                }

                DrawLabel(startX + 4.0f, panelY + 155.0f, "Ustaw kształt wyspy i kliknij\n'Generuj', aby stworzyć nowy\nzarys lądu.", 10, CLR_TEXT);
            }
            else if (sim.activeGodTab == 1) { // Zatoki
                DrawUpDownRow(startX, panelY + 48.0f, rowW, "Liczba zatok", sim.upDownLzatok, 1, 99);
                DrawUpDownRow(startX, panelY + 74.0f, rowW, "Rozmiar", sim.upDownWZatok, 1, 1000, 5);
                DrawUpDownRow(startX, panelY + 100.0f, rowW, "Nieregularność", sim.upDownRZatok, 0, 999, 5);

                if (DrawButton({ startX + 10.0f, panelY + 134.0f, rowW - 20.0f, 32.0f }, "Dodaj zatoki")) {
                    sim.dodajZatoki(sim.upDownLzatok, sim.upDownWZatok, sim.upDownRZatok);
                }
                if (DrawButton({ startX + 10.0f, panelY + 176.0f, rowW - 20.0f, 32.0f }, "Dodaj zatoki na plaży")) {
                    sim.dodajZatokiPlaza(sim.upDownLzatok, sim.upDownWZatok, sim.upDownRZatok);
                }
            }
            else if (sim.activeGodTab == 2) { // Korekta
                DrawLabel(startX + 14.0f, panelY + 48.0f, "Powiększ", 10, CLR_NAVY);
                if (DrawButton({ startX + 10.0f, panelY + 64.0f, 64.0f, 44.0f }, "+")) {
                    sim.zwiekszLad();
                }

                DrawLabel(startX + 114.0f, panelY + 48.0f, "Pomniejsz", 10, CLR_NAVY);
                if (DrawButton({ startX + 110.0f, panelY + 64.0f, 64.0f, 44.0f }, "-")) {
                    sim.zmniejszLad();
                }

                DrawUpDownRow(startX, panelY + 126.0f, rowW, "Wygładzanie", sim.upDownGladz, 1, 20);
                if (DrawButton({ startX + 10.0f, panelY + 160.0f, rowW - 20.0f, 32.0f }, "Wygładź brzeg")) {
                    sim.wygladz(sim.upDownGladz);
                }
            }
            else if (sim.activeGodTab == 3) { // Wnętrze
                if (DrawUpDownRow(startX, panelY + 48.0f, rowW, "Plaża", sim.upDownPlaza, 0, 200, 5) ||
                    DrawUpDownRow(startX, panelY + 72.0f, rowW, "Trawa", sim.upDownTrawa, 0, 200, 5) ||
                    DrawUpDownRow(startX, panelY + 96.0f, rowW, "Śnieg", sim.upDownSnieg, 0, 200, 5)) {
                    sim.pallad();
                }

                DrawUpDownRow(startX, panelY + 124.0f, rowW, "Ziarnistość", sim.upDownZiarno, 0, 16);

                if (DrawButton({ startX + 10.0f, panelY + 154.0f, rowW - 20.0f, 28.0f }, "Dodaj ziarno")) {
                    sim.dodajZiarno(sim.upDownZiarno);
                }
                if (DrawButton({ startX + 10.0f, panelY + 190.0f, rowW - 20.0f, 28.0f }, "Akceptuj paletę")) {
                    sim.pallad();
                }
            }
        }

        // -------------------------------------------------------------------------
        // POZIOM 1: Generator "Króliczek ver. 1.3.1"
        // -------------------------------------------------------------------------
        else if (sim.poziom == 1) {
            DrawGroupBox(groupBoxRect, "Generator \"Króliczek ver. 1.3.1\"");
            float rowW = panelW - 24.0f;
            float startX = panelX + 12.0f;

            DrawUpDownRow(startX, panelY + 40.0f, rowW, "Króliki", sim.upDownIleK, 1, 999, 10);
            DrawUpDownRow(startX, panelY + 70.0f, rowW, "Stada", sim.upDownStadaK, 1, 16);
            DrawUpDownRow(startX, panelY + 100.0f, rowW, "Rozproszenie", sim.upDownRozpK, 1, 16);

            if (DrawButton({ startX + 16.0f, panelY + 140.0f, rowW - 32.0f, 44.0f }, "Generuj króliki")) {
                sim.generujKroliki(sim.upDownIleK);
            }

            char kCountBuf[64];
            snprintf(kCountBuf, sizeof(kCountBuf), "Populacja królików: %zu", sim.Ktab.size());
            DrawLabel(startX + 8.0f, panelY + 200.0f, kCountBuf, 10, CLR_TEXT);
            DrawLabel(startX + 8.0f, panelY + 224.0f, "Kliknij 'OK >>' na dole,\naby przejść do lisów.", 10, CLR_NAVY);
        }

        // -------------------------------------------------------------------------
        // POZIOM 2: Generator "Lisek ver. 1.3.1"
        // -------------------------------------------------------------------------
        else if (sim.poziom == 2) {
            DrawGroupBox(groupBoxRect, "Generator \"Lisek ver. 1.3.1\"");
            float rowW = panelW - 24.0f;
            float startX = panelX + 12.0f;

            DrawUpDownRow(startX, panelY + 40.0f, rowW, "Lisy", sim.upDownIleL, 1, 999, 5);
            DrawUpDownRow(startX, panelY + 70.0f, rowW, "Stada", sim.upDownStadaL, 1, 16);
            DrawUpDownRow(startX, panelY + 100.0f, rowW, "Rozproszenie", sim.upDownRozpL, 1, 16);

            if (DrawButton({ startX + 16.0f, panelY + 140.0f, rowW - 32.0f, 44.0f }, "Generuj lisy")) {
                sim.generujLisy(sim.upDownIleL);
            }

            char lCountBuf[64];
            snprintf(lCountBuf, sizeof(lCountBuf), "Populacja lisów: %zu", sim.Ltab.size());
            DrawLabel(startX + 8.0f, panelY + 200.0f, lCountBuf, 10, CLR_TEXT);
            DrawLabel(startX + 8.0f, panelY + 224.0f, "Kliknij 'OK >>' na dole,\naby uruchomić ekosystem!", 10, CLR_NAVY);
        }

        // -------------------------------------------------------------------------
        // POZIOM 3: Informer "UB ver. 1.3.6"
        // -------------------------------------------------------------------------
        else if (sim.poziom == 3) {
            DrawGroupBox(groupBoxRect, "Informer \"UB ver. 1.3.6\"");
            float rowW = panelW - 24.0f;
            float startX = panelX + 12.0f;

            // Dwie linie zakładek Borland TPageControl MultiLine
            const char* tabsRow1[] = { "Trawka", "Króliki", "Lisy", "Stat" };
            const char* tabsRow2[] = { "Mój królik", "Mój lis", "Ewolucja" };

            Rectangle tabR1 = { panelX + 6.0f, panelY + 16.0f, panelW - 12.0f, 18.0f };
            Rectangle tabR2 = { panelX + 6.0f, panelY + 34.0f, panelW - 12.0f, 18.0f };

            int curR1 = (sim.activeInformerTab < 4) ? sim.activeInformerTab : -1;
            int selR1 = DrawTabs(tabR1, tabsRow1, 4, curR1);
            if (selR1 != curR1 && selR1 >= 0) sim.activeInformerTab = selR1;

            int curR2 = (sim.activeInformerTab >= 4) ? (sim.activeInformerTab - 4) : -1;
            int selR2 = DrawTabs(tabR2, tabsRow2, 3, curR2);
            if (selR2 != curR2 && selR2 >= 0) sim.activeInformerTab = selR2 + 4;

            float baseY = panelY + 56.0f;

            if (sim.activeInformerTab == 0) { // Trawka
                DrawUpDownRow(startX, baseY + 6.0f, rowW, "Wegetacja", sim.wegetacja, 1, 100);

                if (DrawButton({ startX + 10.0f, baseY + 42.0f, rowW - 20.0f, 34.0f }, "Zazieleń (max)")) {
                    sim.maxTrawa();
                }
                if (DrawButton({ startX + 10.0f, baseY + 88.0f, rowW - 20.0f, 34.0f }, "Reset trawy")) {
                    sim.resetTrawy();
                }
                if (DrawButton({ startX + 10.0f, baseY + 134.0f, rowW - 20.0f, 34.0f }, "Skoś trawę (min)")) {
                    sim.minTrawa();
                }
            }
            else if (sim.activeInformerTab == 1) { // Króliki
                bool ch = false;
                ch |= DrawUpDownRow(startX, baseY +   0.0f, rowW, "v królika", sim.vkVal, 1, 50, 1, "0.1x");
                ch |= DrawUpDownRow(startX, baseY +  22.0f, rowW, "metabolizm", sim.metaKVal, 1, 50);
                ch |= DrawUpDownRow(startX, baseY +  44.0f, rowW, "kęs", sim.kesKVal, 1, 255);
                ch |= DrawUpDownRow(startX, baseY +  66.0f, rowW, "żołądek", sim.zoladekKVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY +  88.0f, rowW, "głód", sim.glodKVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 110.0f, rowW, "GŁÓD!", sim.starvingKVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 132.0f, rowW, "detekcja", sim.detekcjaKVal, 1, 200, 5);
                ch |= DrawUpDownRow(startX, baseY + 154.0f, rowW, "dł. życia", sim.zycieKVal, 1, 1000, 10);
                ch |= DrawUpDownRow(startX, baseY + 176.0f, rowW, "dojrzałość", sim.dojrzaloscKVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 198.0f, rowW, "ciąża", sim.ciazaKVal, 1, 1000, 5);
                if (ch) sim.applyKrolikParams();
            }
            else if (sim.activeInformerTab == 2) { // Lisy
                bool ch = false;
                ch |= DrawUpDownRow(startX, baseY +   0.0f, rowW, "v lisa", sim.vlVal, 1, 50, 1, "0.1x");
                ch |= DrawUpDownRow(startX, baseY +  24.0f, rowW, "metabolizm", sim.metaLVal, 1, 50);
                ch |= DrawUpDownRow(startX, baseY +  48.0f, rowW, "w.odż.", sim.wodzLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY +  72.0f, rowW, "żołądek", sim.zoladekLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY +  96.0f, rowW, "głód", sim.glodLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY + 120.0f, rowW, "dł. życia", sim.zycieLVal, 1, 5000, 50);
                ch |= DrawUpDownRow(startX, baseY + 144.0f, rowW, "dojrzałość", sim.dojrzaloscLVal, 1, 1000, 5);
                ch |= DrawUpDownRow(startX, baseY + 168.0f, rowW, "ciąża", sim.ciazaLVal, 1, 1000, 5);
                if (ch) sim.applyLisParams();
            }
            else if (sim.activeInformerTab == 3) { // Statystyki
                char bKr[32], bLi[32], bZ1K[32], bZ2K[32], bZ3K[32], bZ1L[32], bZ2L[32];
                snprintf(bKr, sizeof(bKr), "%zu", sim.Ktab.size());
                snprintf(bLi, sizeof(bLi), "%zu", sim.Ltab.size());
                snprintf(bZ1K, sizeof(bZ1K), "%d", sim.krol ? sim.krol->z1 : 0);
                snprintf(bZ2K, sizeof(bZ2K), "%d", sim.krol ? sim.krol->z2 : 0);
                snprintf(bZ3K, sizeof(bZ3K), "%d", sim.lis ? sim.lis->z3 : 0);
                snprintf(bZ1L, sizeof(bZ1L), "%d", sim.lis ? sim.lis->z1 : 0);
                snprintf(bZ2L, sizeof(bZ2L), "%d", sim.lis ? sim.lis->z2 : 0);

                DrawReadOnlyEditRow(startX, baseY +   0.0f, rowW, "Króliki żywe", bKr);
                DrawReadOnlyEditRow(startX, baseY +  24.0f, rowW, "Lisy żywe", bLi);
                DrawReadOnlyEditRow(startX, baseY +  48.0f, rowW, "Zgon K (głód)", bZ1K);
                DrawReadOnlyEditRow(startX, baseY +  72.0f, rowW, "Zgon K (wiek)", bZ2K);
                DrawReadOnlyEditRow(startX, baseY +  96.0f, rowW, "K pożarte", bZ3K);
                DrawReadOnlyEditRow(startX, baseY + 120.0f, rowW, "Zgon L (głód)", bZ1L);
                DrawReadOnlyEditRow(startX, baseY + 144.0f, rowW, "Zgon L (wiek)", bZ2L);
            }
            else if (sim.activeInformerTab == 4) { // Mój królik
                int maxK = (sim.Ktab.size() > 0) ? ((int)sim.Ktab.size() - 1) : 0;
                DrawUpDownRow(startX, baseY + 0.0f, rowW, "Numer królika", sim.selectedKrolikIdx, 0, maxK);

                if (sim.selectedKrolikIdx >= 0 && sim.selectedKrolikIdx < (int)sim.Ktab.size()) {
                    const auto& k = sim.Ktab[sim.selectedKrolikIdx];
                    const char* stStr = "nieznany";
                    switch (k.status) {
                        case 3: stStr = "szuka pary"; break;
                        case 2: stStr = "głód"; break;
                        case 1: stStr = "ucieka!"; break;
                        case 0: stStr = "GŁÓD!"; break;
                    }
                    char bWiek[32], bZol[32], bCiaz[32], bWielk[32];
                    snprintf(bWiek, sizeof(bWiek), "%d / %d", k.wiek, sim.zycieKVal);
                    snprintf(bZol, sizeof(bZol), "%.1f", k.zoladek);
                    if (k.ciaza >= 0) snprintf(bCiaz, sizeof(bCiaz), "%d", k.ciaza);
                    else snprintf(bCiaz, sizeof(bCiaz), "---");
                    snprintf(bWielk, sizeof(bWielk), "%.2f", k.wielkosc);

                    DrawReadOnlyEditRow(startX, baseY +  26.0f, rowW, "status", stStr);
                    DrawReadOnlyEditRow(startX, baseY +  50.0f, rowW, "płeć", k.plec ? "ON (samiec)" : "ONA (samica)");
                    DrawReadOnlyEditRow(startX, baseY +  74.0f, rowW, "wiek", bWiek);
                    DrawReadOnlyEditRow(startX, baseY +  98.0f, rowW, "żołądek", bZol);
                    DrawReadOnlyEditRow(startX, baseY + 122.0f, rowW, "ciąża", bCiaz);
                    DrawReadOnlyEditRow(startX, baseY + 146.0f, rowW, "wielkość", bWielk);
                } else {
                    DrawLabel(startX + 10.0f, baseY + 40.0f, "Brak królika o tym numerze.", 10, CLR_TEXT);
                }
            }
            else if (sim.activeInformerTab == 5) { // Mój lis
                int maxL = (sim.Ltab.size() > 0) ? ((int)sim.Ltab.size() - 1) : 0;
                DrawUpDownRow(startX, baseY + 0.0f, rowW, "Numer lisa", sim.selectedLisIdx, 0, maxL);

                if (sim.selectedLisIdx >= 0 && sim.selectedLisIdx < (int)sim.Ltab.size()) {
                    const auto& l = sim.Ltab[sim.selectedLisIdx];
                    const char* stStr = "nieznany";
                    switch (l.status) {
                        case 2: stStr = "szuka pary"; break;
                        case 1: stStr = "goni królika"; break;
                        case 0: stStr = "kręcioła"; break;
                    }
                    char bWiek[32], bZol[32], bCiaz[32], bWielk[32];
                    snprintf(bWiek, sizeof(bWiek), "%d / %d", l.wiek, sim.zycieLVal);
                    snprintf(bZol, sizeof(bZol), "%.1f", l.zoladek);
                    if (l.ciaza >= 0) snprintf(bCiaz, sizeof(bCiaz), "%d", l.ciaza);
                    else snprintf(bCiaz, sizeof(bCiaz), "---");
                    snprintf(bWielk, sizeof(bWielk), "%.2f", l.wielkosc);

                    DrawReadOnlyEditRow(startX, baseY +  26.0f, rowW, "status", stStr);
                    DrawReadOnlyEditRow(startX, baseY +  50.0f, rowW, "płeć", l.plec ? "ON (samiec)" : "ONA (samica)");
                    DrawReadOnlyEditRow(startX, baseY +  74.0f, rowW, "wiek", bWiek);
                    DrawReadOnlyEditRow(startX, baseY +  98.0f, rowW, "żołądek", bZol);
                    DrawReadOnlyEditRow(startX, baseY + 122.0f, rowW, "ciąża", bCiaz);
                    DrawReadOnlyEditRow(startX, baseY + 146.0f, rowW, "wielkość", bWielk);
                } else {
                    DrawLabel(startX + 10.0f, baseY + 40.0f, "Brak lisa o tym numerze.", 10, CLR_TEXT);
                }
            }
            else if (sim.activeInformerTab == 6) { // Ewolucja
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

                DrawLabel(startX, baseY + 2.0f, "Średnie króliki:", 10, CLR_NAVY);
                DrawReadOnlyEditRow(startX, baseY + 18.0f, rowW, "wielkość", bWK);
                DrawReadOnlyEditRow(startX, baseY + 42.0f, rowW, "głód", bGK);
                DrawReadOnlyEditRow(startX, baseY + 66.0f, rowW, "GŁÓD!", bSK);

                DrawLabel(startX, baseY + 96.0f, "Średnie lisy:", 10, CLR_NAVY);
                DrawReadOnlyEditRow(startX, baseY + 112.0f, rowW, "wielkość", bWL);
                DrawReadOnlyEditRow(startX, baseY + 136.0f, rowW, "głód", bGL);
            }
        }

        // -------------------------------------------------------------------------
        // 3. Dolny panel przycisków nawigacyjnych i pełnego ekranu
        // -------------------------------------------------------------------------
        Rectangle bottomPanelRect = { panelX, panelY + panelH + 8.0f, panelW, 110.0f };
        DrawGroupBox(bottomPanelRect, "Nawigacja / Ekran");

        // Przycisk "Powrót"
        bool canGoBack = (sim.poziom > 0);
        if (DrawButton({ panelX + 8.0f, panelY + panelH + 24.0f, 68.0f, 40.0f }, "<< Powrót", canGoBack)) {
            sim.butPowrotClick();
        }

        // Przycisk "OK >>" lub "Pauza/Wznów"
        const char* okText = "OK >>";
        if (sim.poziom == 3) {
            okText = sim.running ? "Pauza (Spacja)" : "Wznów (Spacja)";
        }
        if (DrawButton({ panelX + 82.0f, panelY + panelH + 24.0f, panelW - 90.0f, 40.0f }, okText, true, sim.poziom == 3 ? (sim.running ? CLR_TEXT : RED) : CLR_TEXT)) {
            if (sim.poziom == 3) {
                sim.running = !sim.running;
            } else {
                sim.butOkClick();
            }
        }

        // Przycisk "Pełny ekran (F11)"
        const char* fsText = IsWindowFullscreen() ? "Tryb okienkowy (F11)" : "Pełny ekran (F11)";
        if (DrawButton({ panelX + 8.0f, panelY + panelH + 68.0f, panelW - 16.0f, 34.0f }, fsText)) {
            ToggleFullscreen();
        }

        EndTextureMode();

        // =========================================================================
        // RENDEROWANIE DO OKNA Z ZACHOWANIEM PROPORCJI (LETTERBOX FULLSCREEN)
        // =========================================================================
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
        Rectangle destRec   = { offsetX, offsetY, (float)VIRTUAL_W * scale, (float)VIRTUAL_H * scale };
        Vector2 origin      = { 0.0f, 0.0f };

        DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);

        EndDrawing();
    }

    // Czyszczenie zasobów
    UnloadTexture(islandTexture);
    if (texKrolik.id != 0)  UnloadTexture(texKrolik);
    if (texLis.id != 0)     UnloadTexture(texLis);
    if (texWybrany.id != 0) UnloadTexture(texWybrany);
    UnloadRenderTexture(target);

    CloseWindow();
    return 0;
}
