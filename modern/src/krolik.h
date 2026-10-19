#ifndef KROLIK_H
#define KROLIK_H

#include "zwierze.h"
#include "PlodK.h"

class Krolik : public Zwierze, public PlodK {
public:
    // Status zachowania:
    // 0 - starving (skrajny głód, ignoruje lisy, zjada wszystko)
    // 1 - ucieczka (widzi lisa w polu widzenia)
    // 2 - glodny (szuka i zjada trawę)
    // 3 - sex (szuka partnera do rozrodu)

    int pamiec_trawy[2] = { -1, -1 }; // x, y ostatnio widzianej trawy

    float pojemnoscZ = 100.0f;
    float vk = 0.5f;
    float kes = 64.0f;
    float metabolizm = 4.0f;

    PlodK* plod = nullptr;
};

#endif // KROLIK_H
