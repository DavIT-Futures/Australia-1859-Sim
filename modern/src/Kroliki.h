#ifndef KROLIKI_H
#define KROLIKI_H

#include "krolik.h"
#include "Lis.h"
#include <vector>

class Kroliki : public PlodK {
private:
    int** pole;
    int szer, wys;

    void rusz(int n);
    void stat(int n);
    void dodaj(float x, float y, int zarcie, int kto);
    void def_par(int n, int x, int y, int zoladek);
    void evolve(int n);

public:
    std::vector<Lis>* Ltab;
    std::vector<Krolik>* Ktab;

    Kroliki(int** pole, int szer, int wys, std::vector<Krolik>* Ktab, std::vector<Lis>* Ltab);

    float evol = 0.5f;
    long z1 = 0; // śmierć z głodu
    long z2 = 0; // śmierć ze starości

    // Parametry populacji:
    int pole_widz = 25;
    int dl_ciazy = 20;
    int dl_zycia = 100;
    int wiek_dojrz = 21;

    float pojemnoscZ = 100.0f;
    float kes = 64.0f;
    float vk = 0.5f;
    float metabolizm = 4.0f;

    void czysc();
    void generuj(int l, int s, int r);
    void rusz();
    void kill(int n);
};

#endif // KROLIKI_H
