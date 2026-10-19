#ifndef LISY_H
#define LISY_H

#include "Lis.h"
#include "krolik.h"
#include "PlodL.h"
#include <vector>

class Lisy : public PlodL {
private:
    int** pole;
    int szer, wys;
    int timer = 0;

    void rusz(int n);
    void stat(int n);
    void dodaj(float x, float y, int zarcie, int kto);
    void def_par(int n, int x, int y, int zarcie);
    void evolve(int n);

public:
    int z1 = 0; // śmierć z głodu
    int z2 = 0; // śmierć ze starości
    int z3 = 0; // upolowane króliki
    float evol = 0.5f;

    float pojemnoscZ = 2000.0f;
    float kes = 1500.0f;
    float vl = 1.0f;
    float metabolizm = 3.0f;

    int dl_ciazy = 30;
    int dl_zycia = 800;
    int wiek_dojrz = 30;

    std::vector<Lis>* Ltab;
    std::vector<Krolik>* Ktab;

    Lisy(int** pole, int szer, int wys, std::vector<Krolik>* Ktab, std::vector<Lis>* Ltab);
    void czysc();
    void generuj(int l, int s, int r);
    void rusz();
};

#endif // LISY_H
