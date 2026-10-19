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
    int upDownIleK = 200;
    int upDownStadaK = 8;
    int upDownRozpK = 8;

    // Parametry generatora lisów:
    int upDownIleL = 20;
    int upDownStadaL = 8;
    int upDownRozpL = 8;

    // Parametry Informera:
    int wegetacja = 10;

    // Króliki parametry:
    int vkVal = 5;            // vk = 0.1 * vkVal = 0.5
    int metaKVal = 4;
    int kesKVal = 64;
    int zoladekKVal = 100;
    int glodKVal = 60;
    int starvingKVal = 20;
    int detekcjaKVal = 25;
    int zycieKVal = 100;
    int dojrzaloscKVal = 21;
    int ciazaKVal = 20;

    // Lisy parametry:
    int vlVal = 10;           // vl = 0.1 * vlVal = 1.0
    int metaLVal = 3;
    int wodzLVal = 1500;
    int zoladekLVal = 2000;
    int glodLVal = 1000;
    int zycieLVal = 800;
    int dojrzaloscLVal = 30;
    int ciazaLVal = 30;

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

    void fale();
    void lad();
    void pallad();
};

#endif // SIMULATION_H
