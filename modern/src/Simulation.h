#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <cstdint>
#include "Kroliki.h"
#include "Lisy.h"

class Simulation {
public:
    static const int SZER = 500;
    static const int WYS = 400;
    static const int SLONA = 40;

    int** wyspa;
    int** trawa;

    struct RGBColor {
        uint8_t r, g, b;
    };

    RGBColor pal[800];
    RGBColor fala[SLONA];
    RGBColor falaS[SLONA / 2];

    int plus = 0;

    // Phase:
    // 0 = Island Generator ("Creator ver. 1.4")
    // 1 = Ecosystem Simulation & Management ("Informer ver. 1.4")
    int poziom = 0;

    int activeGodTab = 0;       // 0: Shape, 1: Bays, 2: Adjust, 3: Terrain
    int activeInformerTab = 0;  // 0: Grass, 1: Rabbits, 2: Foxes, 3: Stats, 4: My Rabbit, 5: My Fox, 6: Evolution

    // Parametry terenu (Bóg):
    int amplitude = 130;
    int upDownLzatok = 3;
    int upDownWZatok = 30;
    int upDownRZatok = 88;
    int upDownGladz = 1;
    int upDownZiarno = 8;
    int upDownPlaza = 10;
    int upDownTrawa = 30;
    int upDownSnieg = 50;

    // Parametry generatora królików:
    int upDownIleK = 150;
    int upDownStadaK = 8;
    int upDownRozpK = 8;

    // Foxes generator parameters:
    int upDownIleL = 5;
    int upDownStadaL = 8;
    int upDownRozpL = 8;

    // Informer parameters:
    int wegetacja = 10;

    // Rabbits parameters:
    int vkVal = 6;            // vk = 0.1 * vkVal = 0.6
    int metaKVal = 2;         // Calibrated: 2 allows rabbit to survive fleeing without instant starvation
    int kesKVal = 64;
    int zoladekKVal = 150;
    int glodKVal = 90;
    int starvingKVal = 30;
    int detekcjaKVal = 24;    // Fear radius: 24px (flee when predator gets close)
    int zycieKVal = 120;
    int dojrzaloscKVal = 21;
    int ciazaKVal = 20;

    // Foxes parameters:
    int vlVal = 7;            // vl = 0.1 * vlVal = 0.7
    int metaLVal = 3;
    int wodzLVal = 1800;      // Satiation from caught rabbit keeps fox well-fed without wiping whole herds
    int zoladekLVal = 2000;
    int glodLVal = 1000;
    int zycieLVal = 600;
    int dojrzaloscLVal = 35;
    int ciazaLVal = 35;

    // Inspektor osobnika:
    int selectedKrolikIdx = 0;
    int selectedLisIdx = 0;

    std::vector<Krolik> Ktab;
    std::vector<Lis> Ltab;

    Kroliki* krol;
    Lisy* lis;

    bool running = true;
    int simSpeed = 1;

    Simulation();
    ~Simulation();

    void generujWyspe(int amp);
    void dodajZatoki(int l_zatok, int w_zatok, int r_zatok);
    void dodajZatokiPlaza(int l_zatok, int w_zatok, int r_zatok);
    void wygladz(int gladz);
    void zwiekszLad();
    void zmniejszLad();
    void dodajZiarno(int z);
    void zatwierdzWyspe();

    void generujKroliki(int ile = 200);
    void generujLisy(int ile = 20);
    void resetTrawy();
    void maxTrawa();
    void minTrawa();

    void applyKrolikParams();
    void applyLisParams();

    void butOkClick();
    void butPowrotClick();

    void update();
    void renderToRGBA(uint8_t* rgbaBuffer);

    struct IslandStats {
        int totalGrass = 0;
        int maxGrass = 0;
        float grassPercent = 0.0f;
        int landCells = 0;
        int greenCells = 0;
    };

    IslandStats getIslandStats() const;

    void fale();
    void lad();
    void pallad();
};

#endif // SIMULATION_H
