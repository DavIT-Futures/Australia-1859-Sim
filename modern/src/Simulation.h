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
    int wegetacja = 10;

    // Parametry terenu:
    int upDownPlaza = 10;
    int upDownTrawa = 30;
    int upDownSnieg = 50;
    int upDownZiarno = 8;
    int amplitude = 130;

    std::vector<Krolik> Ktab;
    std::vector<Lis> Ltab;

    Kroliki* krol;
    Lisy* lis;

    bool running = true;
    int simSpeed = 1; // 1x, 2x, 5x, 10x

    Simulation();
    ~Simulation();

    void generujWyspe(int amp);
    void dodajZatoki(int l_zatok, int w_zatok, int r_zatok);
    void dodajZatokiPlaza(int l_zatok, int w_zatok, int r_zatok);
    void wygladz(int gladz);
    void zwiekszLad();
    void zmniejszLad();
    void dodajZiarno(int z);
    void zatwierdzWyspe(); // Faza 2: gotowa do wpuszczenia zwierząt

    void generujKroliki(int ile = 200);
    void generujLisy(int ile = 20);
    void resetTrawy();
    void maxTrawa();
    void minTrawa();

    void update();
    void renderToRGBA(uint8_t* rgbaBuffer);

    void fale();
    void lad();
    void pallad();
};

#endif // SIMULATION_H
