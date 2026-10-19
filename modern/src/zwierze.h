#ifndef ZWIERZE_H
#define ZWIERZE_H

class Zwierze {
public:
    float x = 0.0f;
    float y = 0.0f;     // Położenie
    float zoladek = 0.0f;
    int status = 0;
    int index = -1;     // Index ofiary / łowcy
    bool plec = true;   // true = samiec, false = samica
    int wiek = 0;
    int ciaza = -1;     // < 0 brak; odliczanie w dół do 0
};

#endif // ZWIERZE_H
