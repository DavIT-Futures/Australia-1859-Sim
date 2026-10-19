#define _USE_MATH_DEFINES
#include "Simulation.h"
#include "kolejka.h"
#include <cmath>
#include <cstdlib>
#include <cstring>

static inline int random(int n) {
    if (n <= 0) return 0;
    return rand() % n;
}

Simulation::Simulation() {
    wyspa = new int*[SZER + 1];
    trawa = new int*[SZER + 1];
    for (int x = 0; x <= SZER; x++) {
        wyspa[x] = new int[WYS + 1];
        trawa[x] = new int[WYS + 1];
        for (int y = 0; y <= WYS; y++) {
            wyspa[x][y] = 0;
            trawa[x][y] = 0;
        }
    }

    krol = new Kroliki(trawa, SZER, WYS, &Ktab, &Ltab);
    lis = new Lisy(trawa, SZER, WYS, &Ktab, &Ltab);

    applyKrolikParams();
    applyLisParams();

    // Domyślne fale morskie
    for (int n = 0; n < SLONA / 2; n++) {
        fala[n].r = (uint8_t)(64 - n);
        fala[n].g = (uint8_t)(160 - 2 * n);
        fala[n].b = 255;
    }
    for (int n = SLONA / 2; n < SLONA; n++) {
        fala[n].r = (uint8_t)(64 - SLONA + n);
        fala[n].g = (uint8_t)(160 - SLONA + n);
        fala[n].b = 255;
    }

    // Domyślne fale słodkie
    for (int n = 0; n < SLONA / 2; n++) {
        falaS[n].r = (uint8_t)(64 + 2 * sin(M_PI * n / (SLONA / 8.0)));
        falaS[n].g = (uint8_t)(224 + 4 * sin(M_PI * n / (SLONA / 8.0)));
        falaS[n].b = 255;
    }

    // Start w fazie Generator "Bóg" (poziom 0)
    generujWyspe(amplitude);
}

Simulation::~Simulation() {
    delete krol;
    delete lis;
    for (int x = 0; x <= SZER; x++) {
        delete[] wyspa[x];
        delete[] trawa[x];
    }
    delete[] wyspa;
    delete[] trawa;
}

void Simulation::applyKrolikParams() {
    krol->vk = 0.1f * vkVal;
    krol->metabolizm = (float)metaKVal;
    krol->kes = (float)kesKVal;
    krol->pojemnoscZ = (float)zoladekKVal;
    krol->glod = (float)glodKVal;
    krol->starving = (float)starvingKVal;
    krol->pole_widz = detekcjaKVal;
    krol->dl_zycia = zycieKVal;
    krol->wiek_dojrz = dojrzaloscKVal;
    krol->dl_ciazy = ciazaKVal;
}

void Simulation::applyLisParams() {
    lis->vl = 0.1f * vlVal;
    lis->metabolizm = (float)metaLVal;
    lis->kes = (float)wodzLVal;
    lis->pojemnoscZ = (float)zoladekLVal;
    lis->glod = (float)glodLVal;
    lis->dl_zycia = zycieLVal;
    lis->wiek_dojrz = dojrzaloscLVal;
    lis->dl_ciazy = ciazaLVal;
}

void Simulation::butOkClick() {
    if (poziom == 0) {
        zatwierdzWyspe();
        if (Ktab.empty()) {
            krol->generuj(upDownIleK, upDownStadaK, upDownRozpK);
        }
        if (Ltab.empty()) {
            lis->generuj(upDownIleL, upDownStadaL, upDownRozpL);
        }
        poziom = 1;
        running = true;
    } else {
        running = !running;
    }
}

void Simulation::butPowrotClick() {
    if (poziom == 1) {
        for (int x = 0; x < SZER; x++) {
            for (int y = 0; y < WYS; y++) {
                if (wyspa[x][y] >= 512) wyspa[x][y] = 0;
                trawa[x][y] = 0;
            }
        }
        krol->czysc();
        lis->czysc();
        fale();
        poziom = 0;
        running = false;
    }
}

void Simulation::pallad() {
    int pas = SLONA;

    // Plaża
    for (int n = 0; n < upDownPlaza; n++) {
        pal[pas + n].r = 255;
        pal[pas + n].g = 224;
        pal[pas + n].b = 0;
    }
    pas += upDownPlaza;

    // Plaża / trawa
    for (int n = 0; n < 32; n++) {
        pal[pas + n].r = (uint8_t)(255 - n * 8);
        pal[pas + n].g = (uint8_t)(224 - n);
        pal[pas + n].b = 0;
    }
    pas += 32;

    // Trawa
    for (int n = 0; n < upDownTrawa; n++) {
        pal[pas + n].r = 0;
        pal[pas + n].g = 192;
        pal[pas + n].b = 0;
    }
    pas += upDownTrawa;

    // Trawa / śnieg
    for (int n = 0; n < 32; n++) {
        pal[pas + n].r = (uint8_t)(n * 8);
        pal[pas + n].g = (uint8_t)(192 + n * 2);
        pal[pas + n].b = (uint8_t)(n * 8);
    }
    pas += 32;

    // Śnieg
    for (int n = 0; n < upDownSnieg; n++) {
        pal[pas + n].r = 255;
        pal[pas + n].g = 255;
        pal[pas + n].b = 255;
    }
    pas += upDownSnieg;

    // Śnieg / skały
    for (int n = 0; n < 32; n++) {
        uint8_t val = (uint8_t)(255 - n * 8);
        pal[pas + n].r = val;
        pal[pas + n].g = val;
        pal[pas + n].b = val;
    }
    pas += 32;

    // Ziemia
    for (int n = 0; n < 8; n++) {
        pal[pas + n].r = 0;
        pal[pas + n].g = 0;
        pal[pas + n].b = 0;
    }
    pas += 8;

    // Ziemia / lawa
    for (int n = 0; n < 16; n++) {
        pal[pas + n].r = (uint8_t)(n * 16);
        pal[pas + n].g = 0;
        pal[pas + n].b = 0;
    }
    pas += 16;

    // Lawa / ogień
    for (int n = 0; n < 32; n++) {
        pal[pas + n].r = 255;
        pal[pas + n].g = (uint8_t)(n * 8);
        pal[pas + n].b = 0;
    }
    pas += 32;

    // Ogień
    for (int n = pas; n < 512; n++) {
        pal[n].r = 255;
        pal[n].g = 255;
        pal[n].b = 0;
    }
}

void Simulation::lad() {
    pallad();

    FIFO* Kol = new FIFO();
    int x, y, c;

    for (x = 0; x < SZER; x++) {
        for (y = 0; y < WYS; y++) {
            if (wyspa[x][y] < SLONA) {
                Kol->push(x, y, SLONA);
            }
        }
    }

    while (!Kol->empty()) {
        Kol->pop(x, y, c);
        c++;
        if ((y > 0) && (wyspa[x][y - 1] == SLONA)) { wyspa[x][y - 1] = c + 1; Kol->push(x, y - 1, c); }
        if ((y < WYS - 1) && (wyspa[x][y + 1] == SLONA)) { wyspa[x][y + 1] = c + 1; Kol->push(x, y + 1, c); }
        if ((x < SZER - 1) && (wyspa[x + 1][y] == SLONA)) { wyspa[x + 1][y] = c + 1; Kol->push(x + 1, y, c); }
        if ((x > 0) && (wyspa[x - 1][y] == SLONA)) { wyspa[x - 1][y] = c + 1; Kol->push(x - 1, y, c); }
    }

    delete Kol;
}

void Simulation::fale() {
    int x, y;
    for (x = 0; x < SZER; x++) {
        for (y = 0; y < WYS; y++) {
            if (wyspa[x][y] >= SLONA) wyspa[x][y] = 0;
            else wyspa[x][y] = -1;
        }
    }

    FIFO* Kol = new FIFO();
    int c;

    for (x = 0; x < SZER; x++) {
        for (y = 0; y < WYS; y++) {
            if (wyspa[x][y] == 0) Kol->push(x, y, 0);
        }
    }

    while (!Kol->empty()) {
        Kol->pop(x, y, c);
        c++;
        if ((y > 0) && (wyspa[x][y - 1] == -1)) { wyspa[x][y - 1] = c; Kol->push(x, y - 1, c); }
        if ((y < WYS - 1) && (wyspa[x][y + 1] == -1)) { wyspa[x][y + 1] = c; Kol->push(x, y + 1, c); }
        if ((x < SZER - 1) && (wyspa[x + 1][y] == -1)) { wyspa[x + 1][y] = c; Kol->push(x + 1, y, c); }
        if ((x > 0) && (wyspa[x - 1][y] == -1)) { wyspa[x - 1][y] = c; Kol->push(x - 1, y, c); }
    }

    delete Kol;

    for (x = 0; x < SZER; x++) {
        for (y = 0; y < WYS; y++) {
            if (wyspa[x][y] != 0) wyspa[x][y] = wyspa[x][y] % SLONA;
            else wyspa[x][y] = SLONA;
        }
    }

    lad();
}

void Simulation::generujWyspe(int amp) {
    this->amplitude = amp;
    int zaok = amp;
    if (zaok >= WYS) zaok = WYS - 10;

    for (int x = 0; x < SZER; x++) {
        for (int y = 0; y < WYS; y++) {
            wyspa[x][y] = SLONA;
        }
    }

    int y1 = 10, y2 = 10;
    for (int x = 0; x < SZER; x++) {
        y1 += random(3) - 1;
        y2 += random(3) - 1;
        int sy = (int)(zaok * sin(x * M_PI / SZER) - zaok);
        if (y1 < 1) y1 = 1;
        if (y2 < 1) y2 = 1;

        for (int y = 0; y < y1 - sy && y < WYS; y++) wyspa[x][y] = 0;
        for (int y = WYS - y2 + sy; y < WYS; y++) {
            if (y >= 0) wyspa[x][y] = 0;
        }
    }

    int x1 = 10, x2 = 10;
    for (int y = 0; y < WYS; y++) {
        x1 += random(3) - 1;
        x2 += random(3) - 1;
        int sx = (int)(zaok * sin(y * M_PI / WYS) - zaok);
        if (x1 < 1) x1 = 1;
        if (x2 < 1) x2 = 1;

        for (int x = 0; x < x1 - sx && x < SZER; x++) wyspa[x][y] = 0;
        for (int x = SZER - x2 + sx; x < SZER; x++) {
            if (x >= 0) wyspa[x][y] = 0;
        }
    }

    fale();
}

void Simulation::dodajZatoki(int l_zatok, int w_zatok, int r_zatok) {
    for (int n = 0; n < l_zatok; n++) {
        FIFO* Kol = new FIFO();
        int c = 0, x, y;
        do {
            x = random(SZER);
            y = random(WYS);
            c++;
        } while (c < 100000 && wyspa[x][y] < SLONA);

        Kol->push(x, y, 0);

        while (!Kol->empty()) {
            Kol->pop(x, y, c);
            c++;
            if (c < w_zatok) {
                if ((y > 0) && (wyspa[x][y - 1] >= SLONA)) { wyspa[x][y - 1] = 0; Kol->push(x, y - 1, c); }
                if ((y < WYS - 1) && (wyspa[x][y + 1] >= SLONA)) { wyspa[x][y + 1] = 0; Kol->push(x, y + 1, c); }
                if ((x < SZER - 1) && (wyspa[x + 1][y] >= SLONA)) { wyspa[x + 1][y] = 0; Kol->push(x + 1, y, c); }
                if ((x > 0) && (wyspa[x - 1][y] >= SLONA)) { wyspa[x - 1][y] = 0; Kol->push(x - 1, y, c); }
            } else {
                for (int m = 0; m < r_zatok; m++) {
                    wyspa[x][y] = 0;
                    x += random(3) - 1;
                    y += random(3) - 1;
                    if (y < 0) y = 0;
                    if (y >= WYS) y = WYS - 1;
                    if (x < 0) x = 0;
                    if (x >= SZER) x = SZER - 1;
                }
            }
        }
        delete Kol;
    }
    fale();
}

void Simulation::dodajZatokiPlaza(int l_zatok, int w_zatok, int r_zatok) {
    for (int n = 0; n < l_zatok; n++) {
        FIFO* Kol = new FIFO();
        int c = 0, x, y;
        do {
            x = random(SZER);
            y = random(WYS);
            c++;
        } while (c < 100000 && (wyspa[x][y] < SLONA || wyspa[x][y] > 42));

        Kol->push(x, y, 0);

        while (!Kol->empty()) {
            Kol->pop(x, y, c);
            c++;
            if (c < w_zatok && wyspa[x][y] <= 42) {
                if ((y > 0) && (wyspa[x][y - 1] >= SLONA)) { wyspa[x][y - 1] = 0; Kol->push(x, y - 1, c); }
                if ((y < WYS - 1) && (wyspa[x][y + 1] >= SLONA)) { wyspa[x][y + 1] = 0; Kol->push(x, y + 1, c); }
                if ((x < SZER - 1) && (wyspa[x + 1][y] >= SLONA)) { wyspa[x + 1][y] = 0; Kol->push(x + 1, y, c); }
                if ((x > 0) && (wyspa[x - 1][y] >= SLONA)) { wyspa[x - 1][y] = 0; Kol->push(x - 1, y, c); }
            } else {
                for (int m = 0; m < r_zatok; m++) {
                    wyspa[x][y] = 0;
                    x += random(3) - 1;
                    y += random(3) - 1;
                    if (y < 0) y = 0;
                    if (y >= WYS) y = WYS - 1;
                    if (x < 0) x = 0;
                    if (x >= SZER) x = SZER - 1;
                }
            }
        }
        delete Kol;
    }
    fale();
}

void Simulation::wygladz(int gladz) {
    FIFO* Kol = new FIFO();
    int x, y, c;

    // Część 1: erozja
    for (x = 0; x < SZER; x++) {
        for (y = 0; y < WYS; y++) {
            if (wyspa[x][y] < SLONA) Kol->push(x, y, 0);
        }
    }

    while (!Kol->empty()) {
        Kol->pop(x, y, c);
        if (c < gladz) {
            c++;
            if ((y > 0) && (wyspa[x][y - 1] >= SLONA)) { wyspa[x][y - 1] = 0; Kol->push(x, y - 1, c); }
            if ((y < WYS - 1) && (wyspa[x][y + 1] >= SLONA)) { wyspa[x][y + 1] = 0; Kol->push(x, y + 1, c); }
            if ((x < SZER - 1) && (wyspa[x + 1][y] >= SLONA)) { wyspa[x + 1][y] = 0; Kol->push(x + 1, y, c); }
            if ((x > 0) && (wyspa[x - 1][y] >= SLONA)) { wyspa[x - 1][y] = 0; Kol->push(x - 1, y, c); }
        }
    }

    // Część 2: dylatacja
    for (x = 0; x < SZER; x++) {
        for (y = 0; y < WYS; y++) {
            if (wyspa[x][y] >= SLONA) Kol->push(x, y, 0);
        }
    }

    while (!Kol->empty()) {
        Kol->pop(x, y, c);
        if (c < gladz) {
            c++;
            if ((y > 0) && (wyspa[x][y - 1] < SLONA)) { wyspa[x][y - 1] = SLONA; Kol->push(x, y - 1, c); }
            if ((y < WYS - 1) && (wyspa[x][y + 1] < SLONA)) { wyspa[x][y + 1] = SLONA; Kol->push(x, y + 1, c); }
            if ((x < SZER - 1) && (wyspa[x + 1][y] < SLONA)) { wyspa[x + 1][y] = SLONA; Kol->push(x + 1, y, c); }
            if ((x > 0) && (wyspa[x - 1][y] < SLONA)) { wyspa[x - 1][y] = SLONA; Kol->push(x - 1, y, c); }
        }
    }

    delete Kol;
    fale();
}

void Simulation::zwiekszLad() {
    FIFO* Kol = new FIFO();
    int x, y, c;
    for (x = 0; x < SZER; x++)
        for (y = 0; y < WYS; y++)
            if (wyspa[x][y] >= SLONA) Kol->push(x, y, 0);

    while (!Kol->empty()) {
        Kol->pop(x, y, c);
        if ((y > 0) && (wyspa[x][y - 1] < SLONA)) wyspa[x][y - 1] = SLONA;
        if ((y < WYS - 1) && (wyspa[x][y + 1] < SLONA)) wyspa[x][y + 1] = SLONA;
        if ((x < SZER - 1) && (wyspa[x + 1][y] < SLONA)) wyspa[x + 1][y] = SLONA;
        if ((x > 0) && (wyspa[x - 1][y] < SLONA)) wyspa[x - 1][y] = SLONA;
    }
    delete Kol;
    fale();
}

void Simulation::zmniejszLad() {
    FIFO* Kol = new FIFO();
    int x, y, c;
    for (x = 0; x < SZER; x++)
        for (y = 0; y < WYS; y++)
            if (wyspa[x][y] < SLONA) Kol->push(x, y, 0);

    while (!Kol->empty()) {
        Kol->pop(x, y, c);
        if ((y > 0) && (wyspa[x][y - 1] >= SLONA)) wyspa[x][y - 1] = 0;
        if ((y < WYS - 1) && (wyspa[x][y + 1] >= SLONA)) wyspa[x][y + 1] = 0;
        if ((x < SZER - 1) && (wyspa[x + 1][y] >= SLONA)) wyspa[x + 1][y] = 0;
        if ((x > 0) && (wyspa[x - 1][y] >= SLONA)) wyspa[x - 1][y] = 0;
    }
    delete Kol;
    fale();
}

void Simulation::dodajZiarno(int z) {
    int gora = upDownPlaza + upDownTrawa + upDownSnieg + 138;
    for (int x = 0; x < SZER; x++) {
        for (int y = 0; y < WYS; y++) {
            if (wyspa[x][y] >= SLONA) {
                if (wyspa[x][y] < gora) {
                    wyspa[x][y] += random(z + 1) - random(z + 1);
                    if (wyspa[x][y] >= 512) wyspa[x][y] = 511;
                    if (wyspa[x][y] < SLONA) wyspa[x][y] = SLONA;
                } else {
                    wyspa[x][y] += (int)(5.0 * sin(1.0 * x / 8.0) + 5.0 * sin(1.0 * y / 8.0));
                    if (wyspa[x][y] >= 512) wyspa[x][y] = 511;
                    if (wyspa[x][y] < gora) wyspa[x][y] = gora;
                }
            }
        }
    }
}

void Simulation::resetTrawy() {
    int min = SLONA + upDownPlaza;
    int max = SLONA + upDownPlaza + upDownTrawa + 64;
    int max2 = max + upDownSnieg + 32;

    for (int x = 0; x < SZER; x++) {
        for (int y = 0; y < WYS; y++) {
            if (wyspa[x][y] >= 512) {
                wyspa[x][y] = (wyspa[x][y] - 512) / 2 + 512;
            }

            int a = wyspa[x][y];
            if ((a >= min) && (a < max)) {
                if (a < min + 32) trawa[x][y] = 8 * (a - min);
                else if (a > max - 32) trawa[x][y] = 8 * (max - a);
                else trawa[x][y] = 255;
            } else if (a <= SLONA) {
                trawa[x][y] = -255;
            } else if (a >= max) {
                if (a >= max2) trawa[x][y] = max - a;
                else trawa[x][y] = 0;
            } else {
                trawa[x][y] = 0;
            }
        }
    }
}

void Simulation::maxTrawa() {
    for (int x = 0; x < SZER; x++) {
        for (int y = 0; y < WYS; y++) {
            if (trawa[x][y] > 0) trawa[x][y] = 255;
        }
    }
}

void Simulation::minTrawa() {
    for (int x = 0; x < SZER; x++) {
        for (int y = 0; y < WYS; y++) {
            if (trawa[x][y] > 0) trawa[x][y] = 1;
        }
    }
}

void Simulation::zatwierdzWyspe() {
    for (int x = 0; x < SZER; x++) {
        for (int y = 0; y < WYS; y++) {
            if (wyspa[x][y] < SLONA) wyspa[x][y] += 512;
        }
    }

    // BFS słodka woda z rogu (0, 0)
    FIFO* Kol = new FIFO();
    int c, x, y;
    Kol->push(0, 0, 0);

    while (!Kol->empty()) {
        Kol->pop(x, y, c);
        if ((y > 0) && (wyspa[x][y - 1] >= 512)) { Kol->push(x, y - 1, 0); wyspa[x][y - 1] -= 512; }
        if ((y < WYS - 1) && (wyspa[x][y + 1] >= 512)) { Kol->push(x, y + 1, 0); wyspa[x][y + 1] -= 512; }
        if ((x < SZER - 1) && (wyspa[x + 1][y] >= 512)) { Kol->push(x + 1, y, 0); wyspa[x + 1][y] -= 512; }
        if ((x > 0) && (wyspa[x - 1][y] >= 512)) { Kol->push(x - 1, y, 0); wyspa[x - 1][y] -= 512; }
    }
    delete Kol;

    resetTrawy();
    pallad();
}

void Simulation::generujKroliki(int ile) {
    krol->generuj(ile, upDownStadaK, upDownRozpK);
}

void Simulation::generujLisy(int ile) {
    lis->generuj(ile, upDownStadaL, upDownRozpL);
}

void Simulation::update() {
    if (!running) return;

    for (int step = 0; step < simSpeed; step++) {
        if (poziom >= 1) {
            // Trawa rośnie losowo w zależności od wegetacji
            for (int x = 0; x < SZER; x++) {
                for (int y = 0; y < WYS; y++) {
                    if (trawa[x][y] > 0 && trawa[x][y] < 255) {
                        if (random(wegetacja) == 0) {
                            trawa[x][y]++;
                        }
                    }
                }
            }

            // Ruch królików
            krol->rusz();
            // Ruch lisów
            lis->rusz();
        }

        plus++;
    }

    // Animacja fal morskich (modulacja palety)
    int mod = (int)(SLONA * sin(0.02 * plus));
    while (mod < 0) mod += SLONA;
    for (int n = 0; n < SLONA; n++) {
        int mn = (n + mod) % SLONA;
        pal[n] = fala[mn];
    }

    int modS = (int)((SLONA / 2) * sin(0.01 * plus));
    while (modS < 0) modS += (SLONA / 2);
    for (int n = 0; n < SLONA / 2; n++) {
        int mn = (n + modS) % (SLONA / 2);
        pal[512 + n] = falaS[mn];
    }
}

void Simulation::renderToRGBA(uint8_t* rgbaBuffer) {
    const float zielen = 192.0f / 255.0f;

    for (int y = 0; y < WYS; y++) {
        int rowOffset = y * SZER * 4;
        for (int x = 0; x < SZER; x++) {
            int idx = rowOffset + x * 4;
            int palIdx = wyspa[x][y];
            if (palIdx < 0) palIdx = 0;
            if (palIdx >= 800) palIdx = 799;

            float r = (float)pal[palIdx].r;
            float g = (float)pal[palIdx].g;
            float b = (float)pal[palIdx].b;

            if (trawa[x][y] > 0) {
                float tmpi = (float)trawa[x][y];
                float zi = tmpi * zielen;
                float tmp2 = (255.0f - tmpi) / 255.0f;

                r = r * tmp2;
                g = g * tmp2 + zi;
                b = b * tmp2;
            }

            rgbaBuffer[idx + 0] = (uint8_t)(r > 255.0f ? 255 : (r < 0.0f ? 0 : r));
            rgbaBuffer[idx + 1] = (uint8_t)(g > 255.0f ? 255 : (g < 0.0f ? 0 : g));
            rgbaBuffer[idx + 2] = (uint8_t)(b > 255.0f ? 255 : (b < 0.0f ? 0 : b));
            rgbaBuffer[idx + 3] = 255;
        }
    }
}

Simulation::IslandStats Simulation::getIslandStats() const {
    IslandStats stats;
    for (int x = 0; x < SZER; x += 2) {
        for (int y = 0; y < WYS; y += 2) {
            int a = wyspa[x][y];
            if (a >= SLONA) {
                stats.landCells++;
                int tr = trawa[x][y];
                if (tr > 0) {
                    stats.greenCells++;
                    stats.totalGrass += tr;
                    stats.maxGrass += 255;
                }
            }
        }
    }
    if (stats.maxGrass > 0) {
        stats.grassPercent = (float)stats.totalGrass / (float)stats.maxGrass * 100.0f;
    }
    return stats;
}
