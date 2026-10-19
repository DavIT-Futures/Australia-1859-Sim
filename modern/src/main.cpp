#include "raylib.h"
#include "Simulation.h"
#include <cstdio>
#include <cmath>
#include <vector>

int main() {
    const int screenWidth = 1320;
    const int screenHeight = 840;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Australia 1859 Sim — Predator-Prey Island Ecosystem (Raylib / C++20)");
    SetTargetFPS(60);

    Simulation sim;

    // Buffer RGBA dla mapy 500x400
    std::vector<uint8_t> rgbaBuffer(Simulation::SZER * Simulation::WYS * 4, 255);

    Image islandImage = {
        rgbaBuffer.data(),
        Simulation::SZER,
        Simulation::WYS,
        1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    Texture2D islandTexture = LoadTextureFromImage(islandImage);

    // Załaduj sprite'y zwierząt z folderu assets
    Texture2D texKrolik = LoadTexture("assets/krolik.bmp");
    Texture2D texLis = LoadTexture("assets/lis.bmp");
    Texture2D texWybrany = LoadTexture("assets/wybrany.bmp");

    // Jeśli nie ma assets/, spróbuj ze ścieżki bieżącej
    if (texKrolik.id == 0) texKrolik = LoadTexture("krolik.bmp");
    if (texLis.id == 0) texLis = LoadTexture("lis.bmp");
    if (texWybrany.id == 0) texWybrany = LoadTexture("wybrany.bmp");

    int mapOffsetX = 20;
    int mapOffsetY = 20;
    float mapScale = 2.0f; // 500x400 -> 1000x800

    int selectedType = -1; // 0 = krolik, 1 = lis
    int selectedIndex = -1;

    while (!WindowShouldClose()) {
        // --- Obsługa klawiszy / interakcji ---
        if (IsKeyPressed(KEY_SPACE)) {
            sim.running = !sim.running;
        }
        if (IsKeyPressed(KEY_G)) {
            sim.generujWyspe(sim.amplitude);
            sim.zatwierdzWyspe();
            selectedType = -1;
            selectedIndex = -1;
        }
        if (IsKeyPressed(KEY_B)) {
            sim.dodajZatoki(3, 30, 88);
            sim.zatwierdzWyspe();
        }
        if (IsKeyPressed(KEY_S)) {
            sim.wygladz(2);
            sim.zatwierdzWyspe();
        }
        if (IsKeyPressed(KEY_Z)) {
            sim.dodajZiarno(8);
        }
        if (IsKeyPressed(KEY_K)) {
            sim.krol->generuj(50, 8, 8);
        }
        if (IsKeyPressed(KEY_L)) {
            sim.lis->generuj(10, 8, 8);
        }
        if (IsKeyPressed(KEY_R)) {
            sim.resetTrawy();
        }
        if (IsKeyPressed(KEY_M)) {
            sim.maxTrawa();
        }
        if (IsKeyPressed(KEY_C)) {
            sim.krol->czysc();
            sim.lis->czysc();
            selectedType = -1;
            selectedIndex = -1;
        }
        if (IsKeyPressed(KEY_ONE)) sim.simSpeed = 1;
        if (IsKeyPressed(KEY_TWO)) sim.simSpeed = 2;
        if (IsKeyPressed(KEY_THREE)) sim.simSpeed = 5;
        if (IsKeyPressed(KEY_FOUR)) sim.simSpeed = 10;

        if (IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD)) {
            if (sim.simSpeed < 10) sim.simSpeed++;
        }
        if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)) {
            if (sim.simSpeed > 1) sim.simSpeed--;
        }

        // Kliknięcie myszką na mapie - wybór królika lub lisa
        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (mousePos.x >= mapOffsetX && mousePos.x < mapOffsetX + Simulation::SZER * mapScale &&
                mousePos.y >= mapOffsetY && mousePos.y < mapOffsetY + Simulation::WYS * mapScale) {
                
                float simX = (mousePos.x - mapOffsetX) / mapScale;
                float simY = (mousePos.y - mapOffsetY) / mapScale;

                float minDist = 15.0f;
                selectedType = -1;
                selectedIndex = -1;

                // Sprawdź lisy
                for (size_t i = 0; i < sim.Ltab.size(); i++) {
                    float dist = hypotf(simX - sim.Ltab[i].x, simY - sim.Ltab[i].y);
                    if (dist < minDist) {
                        minDist = dist;
                        selectedType = 1;
                        selectedIndex = (int)i;
                    }
                }

                // Sprawdź króliki
                for (size_t i = 0; i < sim.Ktab.size(); i++) {
                    float dist = hypotf(simX - sim.Ktab[i].x, simY - sim.Ktab[i].y);
                    if (dist < minDist) {
                        minDist = dist;
                        selectedType = 0;
                        selectedIndex = (int)i;
                    }
                }
            }
        }

        // --- Aktualizacja symulacji ---
        sim.update();

        // Generuj piksele mapy i wyślij do GPU
        sim.renderToRGBA(rgbaBuffer.data());
        UpdateTexture(islandTexture, rgbaBuffer.data());

        // --- Rysowanie klatki ---
        BeginDrawing();
        ClearBackground({ 25, 28, 36, 255 });

        // Rysuj mapę wyspy (2x skala)
        DrawTextureEx(islandTexture, { (float)mapOffsetX, (float)mapOffsetY }, 0.0f, mapScale, WHITE);
        DrawRectangleLines(mapOffsetX - 1, mapOffsetY - 1, (int)(Simulation::SZER * mapScale) + 2, (int)(Simulation::WYS * mapScale) + 2, { 70, 80, 95, 255 });

        // Rysuj króliki
        for (size_t i = 0; i < sim.Ktab.size(); i++) {
            float drawX = mapOffsetX + sim.Ktab[i].x * mapScale - 4.0f;
            float drawY = mapOffsetY + sim.Ktab[i].y * mapScale - 4.0f;
            if (texKrolik.id > 0) {
                DrawTextureEx(texKrolik, { drawX, drawY }, 0.0f, 1.5f, WHITE);
            } else {
                DrawCircle((int)(mapOffsetX + sim.Ktab[i].x * mapScale), (int)(mapOffsetY + sim.Ktab[i].y * mapScale), 2.5f, WHITE);
            }
        }

        // Rysuj lisy
        for (size_t i = 0; i < sim.Ltab.size(); i++) {
            float drawX = mapOffsetX + sim.Ltab[i].x * mapScale - 4.0f;
            float drawY = mapOffsetY + sim.Ltab[i].y * mapScale - 4.0f;
            if (texLis.id > 0) {
                DrawTextureEx(texLis, { drawX, drawY }, 0.0f, 1.5f, WHITE);
            } else {
                DrawCircle((int)(mapOffsetX + sim.Ltab[i].x * mapScale), (int)(mapOffsetY + sim.Ltab[i].y * mapScale), 3.5f, RED);
            }
        }

        // Zaznacz wybranego osobnika
        if (selectedType == 0 && selectedIndex >= 0 && selectedIndex < (int)sim.Ktab.size()) {
            float selX = mapOffsetX + sim.Ktab[selectedIndex].x * mapScale - 6.0f;
            float selY = mapOffsetY + sim.Ktab[selectedIndex].y * mapScale - 6.0f;
            if (texWybrany.id > 0) DrawTextureEx(texWybrany, { selX, selY }, 0.0f, 1.5f, WHITE);
            else DrawCircleLines((int)(mapOffsetX + sim.Ktab[selectedIndex].x * mapScale), (int)(mapOffsetY + sim.Ktab[selectedIndex].y * mapScale), 8.0f, YELLOW);
        } else if (selectedType == 1 && selectedIndex >= 0 && selectedIndex < (int)sim.Ltab.size()) {
            float selX = mapOffsetX + sim.Ltab[selectedIndex].x * mapScale - 6.0f;
            float selY = mapOffsetY + sim.Ltab[selectedIndex].y * mapScale - 6.0f;
            if (texWybrany.id > 0) DrawTextureEx(texWybrany, { selX, selY }, 0.0f, 1.5f, WHITE);
            else DrawCircleLines((int)(mapOffsetX + sim.Ltab[selectedIndex].x * mapScale), (int)(mapOffsetY + sim.Ltab[selectedIndex].y * mapScale), 8.0f, YELLOW);
        }

        // --- Panel boczny (Sidebar) ---
        int sbX = 1045;
        int sbY = 20;
        int sbW = 255;
        int sbH = 800;

        DrawRectangle(sbX, sbY, sbW, sbH, { 35, 39, 49, 255 });
        DrawRectangleLines(sbX, sbY, sbW, sbH, { 60, 68, 84, 255 });

        int cy = sbY + 15;
        DrawText("AUSTRALIA 1859 SIM", sbX + 15, cy, 20, GOLD);
        cy += 24;
        DrawText("Predator-Prey Life Simulator", sbX + 15, cy, 12, LIGHTGRAY);
        cy += 20;
        DrawLine(sbX + 15, cy, sbX + sbW - 15, cy, { 60, 68, 84, 255 });
        cy += 12;

        // Status symulacji
        char statusText[64];
        snprintf(statusText, sizeof(statusText), "Status: %s (Speed: %dx)", sim.running ? "RUNNING" : "PAUSED", sim.simSpeed);
        DrawText(statusText, sbX + 15, cy, 14, sim.running ? GREEN : ORANGE);
        cy += 22;

        snprintf(statusText, sizeof(statusText), "FPS: %d | Time: %d", GetFPS(), sim.plus);
        DrawText(statusText, sbX + 15, cy, 12, GRAY);
        cy += 22;
        DrawLine(sbX + 15, cy, sbX + sbW - 15, cy, { 60, 68, 84, 255 });
        cy += 12;

        // Populacja
        DrawText("POPULATION COUNTERS", sbX + 15, cy, 14, SKYBLUE);
        cy += 20;

        char buf[128];
        snprintf(buf, sizeof(buf), "Rabbits (Kroliki): %d", (int)sim.Ktab.size());
        DrawText(buf, sbX + 15, cy, 15, WHITE);
        cy += 18;

        snprintf(buf, sizeof(buf), "Foxes (Lisy): %d", (int)sim.Ltab.size());
        DrawText(buf, sbX + 15, cy, 15, RED);
        cy += 24;

        DrawText("MORTALITY ANALYTICS", sbX + 15, cy, 13, SKYBLUE);
        cy += 18;
        snprintf(buf, sizeof(buf), "Rabbits Starved: %ld", sim.krol->z1);
        DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY);
        cy += 16;
        snprintf(buf, sizeof(buf), "Rabbits Old Age: %ld", sim.krol->z2);
        DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY);
        cy += 16;
        snprintf(buf, sizeof(buf), "Rabbits Hunted: %d", sim.lis->z3);
        DrawText(buf, sbX + 20, cy, 12, RED);
        cy += 16;
        snprintf(buf, sizeof(buf), "Foxes Starved: %d", sim.lis->z1);
        DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY);
        cy += 16;
        snprintf(buf, sizeof(buf), "Foxes Old Age: %d", sim.lis->z2);
        DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY);
        cy += 22;

        DrawLine(sbX + 15, cy, sbX + sbW - 15, cy, { 60, 68, 84, 255 });
        cy += 12;

        // Inspektor osobnika
        DrawText("INSPECTOR (Click Animal)", sbX + 15, cy, 13, YELLOW);
        cy += 18;

        if (selectedType == 0 && selectedIndex >= 0 && selectedIndex < (int)sim.Ktab.size()) {
            const Krolik& k = sim.Ktab[selectedIndex];
            DrawText("Type: RABBIT (Krolik)", sbX + 20, cy, 12, WHITE); cy += 15;
            snprintf(buf, sizeof(buf), "Sex: %s", k.plec ? "Male (ON)" : "Female (ONA)");
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Age: %d / %d", k.wiek, sim.krol->dl_zycia);
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Energy (Stomach): %.1f", k.zoladek);
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Status: %s", 
                k.status == 3 ? "Seeking Mate" : 
                (k.status == 2 ? "Hungry" : 
                (k.status == 1 ? "Fleeing Fox!" : "STARVING!")));
            DrawText(buf, sbX + 20, cy, 12, k.status == 1 ? RED : (k.status == 0 ? MAROON : GREEN)); cy += 15;
            snprintf(buf, sizeof(buf), "Pregnancy: %s", k.ciaza >= 0 ? TextFormat("%d ticks", k.ciaza) : "None");
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Size: %.2f | Hunger: %.1f", k.wielkosc, k.glod);
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 20;
        } else if (selectedType == 1 && selectedIndex >= 0 && selectedIndex < (int)sim.Ltab.size()) {
            const Lis& l = sim.Ltab[selectedIndex];
            DrawText("Type: FOX (Lis)", sbX + 20, cy, 12, RED); cy += 15;
            snprintf(buf, sizeof(buf), "Sex: %s", l.plec ? "Male (ON)" : "Female (ONA)");
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Age: %d / %d", l.wiek, sim.lis->dl_zycia);
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Energy (Stomach): %.1f", l.zoladek);
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Status: %s", 
                l.status == 2 ? "Seeking Mate" : 
                (l.status == 1 ? "HUNTING RABBIT!" : "Circling"));
            DrawText(buf, sbX + 20, cy, 12, l.status == 1 ? RED : (l.status == 2 ? PINK : ORANGE)); cy += 15;
            snprintf(buf, sizeof(buf), "Pregnancy: %s", l.ciaza >= 0 ? TextFormat("%d ticks", l.ciaza) : "None");
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 15;
            snprintf(buf, sizeof(buf), "Size: %.2f | Hunger: %.1f", l.wielkosc, l.glod);
            DrawText(buf, sbX + 20, cy, 12, LIGHTGRAY); cy += 20;
        } else {
            DrawText("No animal selected.", sbX + 20, cy, 12, GRAY);
            cy += 15;
            DrawText("Click on a rabbit or fox.", sbX + 20, cy, 12, GRAY);
            cy += 25;
        }

        DrawLine(sbX + 15, cy, sbX + sbW - 15, cy, { 60, 68, 84, 255 });
        cy += 12;

        // Klawisze i skróty
        DrawText("HOTKEYS & COMMANDS", sbX + 15, cy, 13, SKYBLUE);
        cy += 18;
        DrawText("[SPACE] Pause / Resume", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[1 / 2 / 3] Speed: 1x, 2x, 5x", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[G] Generate New Island", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[B] Carve Coastal Bays", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[S] Smooth Island Coast", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[Z] Add Terrain Grain", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[K] Spawn 50 Rabbits", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[L] Spawn 10 Foxes", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[R] Reset Grass (Vegetation)", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[M] Maximize Grass (Lush)", sbX + 20, cy, 11, WHITE); cy += 14;
        DrawText("[C] Clear All Animals", sbX + 20, cy, 11, WHITE); cy += 16;

        EndDrawing();
    }

    // Czyszczenie zasobów
    if (texKrolik.id > 0) UnloadTexture(texKrolik);
    if (texLis.id > 0) UnloadTexture(texLis);
    if (texWybrany.id > 0) UnloadTexture(texWybrany);
    UnloadTexture(islandTexture);

    CloseWindow();
    return 0;
}
