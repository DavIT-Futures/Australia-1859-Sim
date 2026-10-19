#include "Lisy.h"
#include <cmath>
#include <cstdlib>

static inline int random(int n) {
    if (n <= 0) return 0;
    return rand() % n;
}

Lisy::Lisy(int** pole, int szer, int wys, std::vector<Krolik>* Ktab, std::vector<Lis>* Ltab) {
    this->pole = pole;
    this->szer = szer;
    this->wys = wys;
    this->Ktab = Ktab;
    this->Ltab = Ltab;
    this->timer = 0;

    this->wielkosc = 1.0f;
    this->evol = 0.5f;

    this->z1 = 0;
    this->z2 = 0;
    this->z3 = 0;
}

void Lisy::czysc() {
    for (auto& l : *Ltab) {
        if (l.plod) {
            delete l.plod;
            l.plod = nullptr;
        }
    }
    Ltab->clear();
}

void Lisy::def_par(int n, int x, int y, int zarcie) {
    (*Ltab)[n].x = (float)x;
    (*Ltab)[n].y = (float)y;
    (*Ltab)[n].zoladek = (float)zarcie;
    (*Ltab)[n].wiek = 0;
    (*Ltab)[n].plec = (random(2) != 0);
    (*Ltab)[n].ciaza = -1;
}

void Lisy::evolve(int n) {
    (*Ltab)[n].wielkosc += evol * (random(201) - 100) * (*Ltab)[n].wielkosc / 100.0f;
    (*Ltab)[n].glod += evol * (random(201) - 100) * (*Ltab)[n].glod / 100.0f;

    (*Ltab)[n].pojemnoscZ = this->pojemnoscZ * (*Ltab)[n].wielkosc;
    (*Ltab)[n].vl = this->vl * (*Ltab)[n].wielkosc;
    (*Ltab)[n].metabolizm = this->metabolizm * (*Ltab)[n].wielkosc;
}

void Lisy::generuj(int l, int s, int r) {
    (void)s; (void)r;
    int startIdx = (int)Ltab->size();
    Ltab->resize(startIdx + l);
    for (int n = startIdx; n < startIdx + l; n++) {
        int x, y;
        int attempts = 0;
        do {
            x = random(szer);
            y = random(wys);
            attempts++;
        } while (attempts < 100000 && pole[x][y] <= 0);

        int zarcie = (int)(pojemnoscZ / 2.0f + random((int)(pojemnoscZ / 2.0f) + 1));
        def_par(n, x, y, zarcie);
        (*Ltab)[n].wiek = random((int)(0.2f * dl_zycia) + 1);

        (*Ltab)[n].wielkosc = this->wielkosc;
        (*Ltab)[n].glod = this->glod;
        evolve(n);
    }
}

void Lisy::stat(int n) {
    (*Ltab)[n].status = 2;
    if (((*Ltab)[n].zoladek < (*Ltab)[n].glod) || ((*Ltab)[n].ciaza >= 0)) (*Ltab)[n].status = 1;
    if (Ktab->empty()) (*Ltab)[n].status = 0;
}

void Lisy::rusz() {
    for (size_t n = 0; n < Ltab->size(); n++) stat((int)n);
    for (size_t n = 0; n < Ltab->size(); n++) rusz((int)n);

    int n = 0;
    while (n < (int)Ltab->size()) {
        if (((*Ltab)[n].zoladek < 0) || ((*Ltab)[n].wiek >= dl_zycia)) {
            if ((*Ltab)[n].zoladek < 0) z1++;
            else z2++;

            if ((*Ltab)[n].plod) {
                delete (*Ltab)[n].plod;
                (*Ltab)[n].plod = nullptr;
            }

            (*Ltab)[n] = (*Ltab)[Ltab->size() - 1];
            Ltab->pop_back();
            n--;
        }
        n++;
    }
    timer++;
}

void Lisy::dodaj(float x, float y, int zarcie, int kto) {
    float bx = x + (float)(random(5) - 2);
    float by = y + (float)(random(5) - 2);
    if (bx >= 2 && bx < szer - 2 && by >= 2 && by < wys - 2 && pole[(int)bx][(int)by] >= 0) {
        x = bx;
        y = by;
    }

    Ltab->push_back(Lis());
    int idx = (int)Ltab->size() - 1;
    def_par(idx, (int)x, (int)y, zarcie);

    if ((*Ltab)[kto].plod != nullptr) {
        (*Ltab)[idx].glod = (*Ltab)[kto].plod->glod;
        (*Ltab)[idx].wielkosc = (*Ltab)[kto].plod->wielkosc;
        delete (*Ltab)[kto].plod;
        (*Ltab)[kto].plod = nullptr;
    }

    evolve(idx);
    stat(idx);
}

void Lisy::rusz(int n) {
    float vl = (*Ltab)[n].vl;
    float x = (*Ltab)[n].x;
    float y = (*Ltab)[n].y;

    if ((*Ltab)[n].status == 1 && !Ktab->empty()) {
        float min = 99999.0f, dx, dy, odl;
        int i = -1;

        for (size_t m = 0; m < Ktab->size(); m++) {
            dx = (*Ltab)[n].x - (*Ktab)[m].x;
            dy = (*Ltab)[n].y - (*Ktab)[m].y;
            odl = dx * dx + dy * dy;
            if (odl < min) {
                min = odl;
                i = (int)m;
            }
        }

        if (i >= 0 && i < (int)Ktab->size()) {
            min = sqrtf(min);
            dx = (*Ltab)[n].x - (*Ktab)[i].x;
            dy = (*Ltab)[n].y - (*Ktab)[i].y;

            if (min > 0) {
                if (sqrtf(dx * dx + dy * dy) > vl) {
                    dx = vl * dx / min;
                    dy = vl * dy / min;
                }
            }

            x = (*Ltab)[n].x - dx;
            y = (*Ltab)[n].y - dy;

            if (min < 3.0f) {
                // Lis upolował królika!
                float huntedRabbitWielkosc = (*Ktab)[i].wielkosc;
                if ((*Ktab)[i].plod) {
                    delete (*Ktab)[i].plod;
                    (*Ktab)[i].plod = nullptr;
                }
                (*Ktab)[i] = (*Ktab)[Ktab->size() - 1];
                Ktab->pop_back();

                (*Ltab)[n].zoladek = huntedRabbitWielkosc * kes;
                z3++;
            }
        }
    }

    if ((*Ltab)[n].status == 0) {
        x = (*Ltab)[n].x + 2.0f * sinf(timer / 2.0f + n);
        y = (*Ltab)[n].y + 2.0f * cosf(timer / 2.0f + n);
    }

    if ((*Ltab)[n].status == 2) {
        float min = 999999999.0f, dx, dy, odl;
        int i = -1;

        for (size_t m = 0; m < Ltab->size(); m++) {
            if ((m != (size_t)n) && ((*Ltab)[m].status == 2) && ((*Ltab)[n].plec != (*Ltab)[m].plec) && ((*Ltab)[m].wiek > wiek_dojrz)) {
                dx = (*Ltab)[n].x - (*Ltab)[m].x;
                dy = (*Ltab)[n].y - (*Ltab)[m].y;
                odl = dx * dx + dy * dy;
                if (odl < min) {
                    min = odl;
                    i = (int)m;
                }
            }
        }

        if (min > 0 && i >= 0) min = sqrtf(min);

        if (i >= 0) {
            dx = (*Ltab)[n].x - (*Ltab)[i].x;
            dy = (*Ltab)[n].y - (*Ltab)[i].y;

            if (min > 2.0f) {
                if (min > 0) {
                    dx = vl * dx / min;
                    dy = vl * dy / min;
                }
            }

            x = (*Ltab)[n].x - dx;
            y = (*Ltab)[n].y - dy;

            if ((min < 10.0f) && (Ltab->size() < 6000) && ((*Ltab)[n].ciaza < 0) && ((*Ltab)[n].plec == false)) {
                (*Ltab)[n].ciaza = dl_ciazy;
                if ((*Ltab)[n].plod == nullptr) (*Ltab)[n].plod = new PlodL();

                (*Ltab)[n].plod->wielkosc = ((*Ltab)[n].wielkosc + (*Ltab)[i].wielkosc) / 2.0f;
                (*Ltab)[n].plod->glod = ((*Ltab)[n].glod + (*Ltab)[i].glod) / 2.0f;
            }
        } else {
            dx = (float)(random(3) - 1);
            dy = (float)(random(3) - 1);
            x = (*Ltab)[n].x - dx;
            y = (*Ltab)[n].y - dy;
        }
    }

    if (x >= 0 && x < szer && y >= 0 && y < wys) {
        if (pole[(int)x][(int)y] >= 0) {
            (*Ltab)[n].x = x;
            (*Ltab)[n].y = y;
        }
    }

    if ((*Ltab)[n].ciaza == 0) {
        dodaj((*Ltab)[n].x, (*Ltab)[n].y, (int)((*Ltab)[n].zoladek /= 3.0f), n);
        (*Ltab)[n].zoladek /= 3.0f;
        (*Ltab)[n].ciaza = -1;
    }

    (*Ltab)[n].zoladek -= (*Ltab)[n].metabolizm;
    (*Ltab)[n].wiek++;
    if ((*Ltab)[n].ciaza >= 0) (*Ltab)[n].ciaza--;
}
