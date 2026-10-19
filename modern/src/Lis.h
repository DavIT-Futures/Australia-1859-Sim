#ifndef LIS_H
#define LIS_H

#include "zwierze.h"
#include "PlodL.h"

class Lis : public Zwierze, public PlodL {
public:
    // Status zachowania:
    // 0 - kreciola (kręci się w kółko, gdy na wyspie nie ma królików)
    // 1 - glodny (tropi i poluje na najbliższego królika)
    // 2 - sex (szuka partnera do rozrodu)

    float pojemnoscZ = 2000.0f;
    float vl = 1.0f;
    float metabolizm = 3.0f;

    PlodL* plod = nullptr;
};

#endif // LIS_H
