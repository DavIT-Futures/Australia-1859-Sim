#include "Kroliki.h"
#include <cmath>
#include <cstdlib>

static inline int random(int n) {
    if (n <= 0) return 0;
    return rand() % n;
}

Kroliki::Kroliki(int** pole, int szer, int wys, std::vector<Krolik>* Ktab, std::vector<Lis>* Ltab) {
    this->pole = pole;
    this->szer = szer;
    this->wys = wys;
    this->Ktab = Ktab;
    this->Ltab = Ltab;

    this->wielkosc = 1.0f;
    this->evol = 0.5f;

    this->z1 = 0;
    this->z2 = 0;
}

void Kroliki::czysc() {
    for (auto& k : *Ktab) {
        if (k.plod) {
            delete k.plod;
            k.plod = nullptr;
        }
    }
    Ktab->clear();
}

void Kroliki::def_par(int n, int x, int y, int zoladek) {
    (*Ktab)[n].x = (float)x;
    (*Ktab)[n].y = (float)y;
    (*Ktab)[n].zoladek = (float)zoladek;
    (*Ktab)[n].wiek = 0;
    (*Ktab)[n].plec = (random(2) != 0);
    (*Ktab)[n].ciaza = -1;

    (*Ktab)[n].pamiec_trawy[0] = -1;
    (*Ktab)[n].pamiec_trawy[1] = -1;
}

void Kroliki::evolve(int n) {
    (*Ktab)[n].wielkosc += evol * (random(201) - 100) * (*Ktab)[n].wielkosc / 100.0f;
    (*Ktab)[n].glod += evol * (random(201) - 100) * (*Ktab)[n].glod / 100.0f;
    (*Ktab)[n].starving += evol * (random(201) - 100) * (*Ktab)[n].starving / 100.0f;

    (*Ktab)[n].pojemnoscZ = this->pojemnoscZ * (*Ktab)[n].wielkosc;
    (*Ktab)[n].kes = this->kes * (*Ktab)[n].wielkosc;
    (*Ktab)[n].vk = this->vk * (*Ktab)[n].wielkosc;
    (*Ktab)[n].metabolizm = this->metabolizm * (*Ktab)[n].wielkosc;
}

void Kroliki::generuj(int l, int s, int r) {
    (void)s; (void)r;
    int startIdx = (int)Ktab->size();
    Ktab->resize(startIdx + l);
    for (int n = startIdx; n < startIdx + l; n++) {
        int x, y;
        int attempts = 0;
        do {
            x = random(szer);
            y = random(wys);
            attempts++;
        } while (attempts < 100000 && pole[x][y] <= 0);

        def_par(n, x, y, (int)(pojemnoscZ / 2));
        (*Ktab)[n].wiek = random((int)(0.2f * dl_zycia) + 1);

        (*Ktab)[n].wielkosc = this->wielkosc;
        (*Ktab)[n].glod = this->glod;
        (*Ktab)[n].starving = this->starving;
        evolve(n);
    }
}

#include <algorithm>

static const int CELL_SIZE = 25;
static const int GRID_COLS = 20; // 500 / 25
static const int GRID_ROWS = 16; // 400 / 25
static std::vector<int> s_rabbitGrid[GRID_ROWS][GRID_COLS];

void Kroliki::rusz() {
    // 1. Fast O(N) spatial partitioning for instant mating lookups
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLS; c++) {
            s_rabbitGrid[r][c].clear();
        }
    }
    for (int n = 0; n < (int)Ktab->size(); n++) {
        int gx = (int)(*Ktab)[n].x / CELL_SIZE;
        int gy = (int)(*Ktab)[n].y / CELL_SIZE;
        if (gx >= 0 && gx < GRID_COLS && gy >= 0 && gy < GRID_ROWS) {
            s_rabbitGrid[gy][gx].push_back(n);
        }
    }

    for (size_t n = 0; n < Ktab->size(); n++) stat((int)n);
    for (size_t n = 0; n < Ktab->size(); n++) rusz((int)n);

    int n = 0;
    while (n < (int)Ktab->size()) {
        if (((*Ktab)[n].zoladek < 0) || ((*Ktab)[n].wiek > dl_zycia)) {
            if ((*Ktab)[n].zoladek < 0) z1++;
            else z2++;

            if ((*Ktab)[n].plod) {
                delete (*Ktab)[n].plod;
                (*Ktab)[n].plod = nullptr;
            }

            (*Ktab)[n] = (*Ktab)[Ktab->size() - 1];
            Ktab->pop_back();
            n--;
        }
        n++;
    }
}

void Kroliki::stat(int n) {
    if ((*Ktab)[n].wiek > wiek_dojrz) (*Ktab)[n].status = 3;
    else (*Ktab)[n].status = 2;

    if (((*Ktab)[n].zoladek < (*Ktab)[n].glod) || ((*Ktab)[n].ciaza >= 0)) (*Ktab)[n].status = 2;

    float min = 99999.0f, odl, dx, dy;
    int i = -1;

    for (size_t m = 0; m < Ltab->size(); m++) {
        dx = (*Ktab)[n].x - (*Ltab)[m].x;
        dy = (*Ktab)[n].y - (*Ltab)[m].y;
        odl = dx * dx + dy * dy;
        if (odl < min) {
            min = odl;
            i = (int)m;
        }
    }
    if (i >= 0) min = sqrtf(min);

    if (min < pole_widz) {
        (*Ktab)[n].status = 1;
        (*Ktab)[n].index = i;
    }
    if ((*Ktab)[n].zoladek <= (*Ktab)[n].starving) (*Ktab)[n].status = 0;
}

void Kroliki::dodaj(float x, float y, int zarcie, int kto) {
    float bx = x + (float)(random(5) - 2);
    float by = y + (float)(random(5) - 2);
    if (bx >= 2 && bx < szer - 2 && by >= 2 && by < wys - 2 && pole[(int)bx][(int)by] >= 0) {
        x = bx;
        y = by;
    }

    Ktab->push_back(Krolik());
    int idx = (int)Ktab->size() - 1;
    def_par(idx, (int)x, (int)y, zarcie);

    if ((*Ktab)[kto].plod != nullptr) {
        (*Ktab)[idx].glod = (*Ktab)[kto].plod->glod;
        (*Ktab)[idx].starving = (*Ktab)[kto].plod->starving;
        (*Ktab)[idx].wielkosc = (*Ktab)[kto].plod->wielkosc;
        delete (*Ktab)[kto].plod;
        (*Ktab)[kto].plod = nullptr;
    }

    evolve(idx);
    stat(idx);
}

void Kroliki::rusz(int n) {
    float vk = (*Ktab)[n].vk;
    float x = (*Ktab)[n].x;
    float y = (*Ktab)[n].y;

    if (((*Ktab)[n].status == 0) || ((*Ktab)[n].status == 2)) {
        if (pole[(int)x][(int)y] < 2) {
            int t[10][2];
            int ile = 1;
            t[0][0] = (int)(*Ktab)[n].x;
            t[0][1] = (int)(*Ktab)[n].y;
            int max = pole[t[0][0]][t[0][1]];

            for (int a = -1; a <= 1; a++) {
                for (int b = -1; b <= 1; b++) {
                    int nx = a + (int)(*Ktab)[n].x;
                    int ny = b + (int)(*Ktab)[n].y;
                    if (nx >= 0 && nx < szer && ny >= 0 && ny < wys) {
                        if (pole[nx][ny] > max) {
                            ile = 1;
                            t[0][0] = nx;
                            t[0][1] = ny;
                            max = pole[nx][ny];
                        } else if (pole[nx][ny] == max && ile < 10) {
                            t[ile][0] = nx;
                            t[ile][1] = ny;
                            ile++;
                        }
                    }
                }
            }

            int pick = random(ile);
            x = (float)t[pick][0];
            y = (float)t[pick][1];

            // If local immediate cell has no grass, use memory or forage outward
            if (pole[(int)x][(int)y] <= 0) {
                if ((*Ktab)[n].pamiec_trawy[0] != -1) {
                    float tx = (float)(*Ktab)[n].pamiec_trawy[0];
                    float ty = (float)(*Ktab)[n].pamiec_trawy[1];

                    // Direction TOWARDS remembered grass
                    float dx = tx - (*Ktab)[n].x;
                    float dy = ty - (*Ktab)[n].y;
                    float dist = dx * dx + dy * dy;

                    if (dist > 0.0f) {
                        dist = sqrtf(dist);
                        dx = vk * dx / dist;
                        dy = vk * dy / dist;
                        x = (*Ktab)[n].x + dx;
                        y = (*Ktab)[n].y + dy;
                    }

                    if (dist < 3.0f || (tx >= 0 && tx < szer && ty >= 0 && ty < wys && pole[(int)tx][(int)ty] <= 0)) {
                        (*Ktab)[n].pamiec_trawy[0] = -1;
                        (*Ktab)[n].pamiec_trawy[1] = -1;
                    }
                } else {
                    // Fast directional scent check in 8 compass directions at distance 8, 14, 20
                    static const int offsets[8][2] = {
                        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
                        { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 }
                    };
                    bool found = false;
                    for (int dist = 8; dist <= 20; dist += 6) {
                        for (int d = 0; d < 8; d++) {
                            int nx = (int)(*Ktab)[n].x + offsets[d][0] * dist;
                            int ny = (int)(*Ktab)[n].y + offsets[d][1] * dist;
                            if (nx >= 2 && nx < szer - 2 && ny >= 2 && ny < wys - 2) {
                                if (pole[nx][ny] > 1) {
                                    (*Ktab)[n].pamiec_trawy[0] = nx;
                                    (*Ktab)[n].pamiec_trawy[1] = ny;
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if (found) break;
                    }
                    if (!found) {
                        // Gentle random wander across land to explore the island
                        x = (*Ktab)[n].x + (float)(random(3) - 1);
                        y = (*Ktab)[n].y + (float)(random(3) - 1);
                    }
                }
            }
        } else {
            if (pole[(int)x][(int)y] < (*Ktab)[n].kes + 1) {
                (*Ktab)[n].zoladek += pole[(int)x][(int)y];
                pole[(int)x][(int)y] = 1;
            } else {
                (*Ktab)[n].zoladek += (*Ktab)[n].kes;
                pole[(int)x][(int)y] -= (int)(*Ktab)[n].kes;
            }
        }
    }

    if ((*Ktab)[n].status == 1) {
        int i = (*Ktab)[n].index;
        if (i >= 0 && i < (int)Ltab->size()) {
            float dx = (*Ktab)[n].x - (*Ltab)[i].x;
            float dy = (*Ktab)[n].y - (*Ltab)[i].y;
            float min = dx * dx + dy * dy;
            if (min > 0) {
                min = sqrtf(min);
                dx = vk * dx / min;
                dy = vk * dy / min;
            }
            x = (*Ktab)[n].x + dx;
            y = (*Ktab)[n].y + dy;
        }
    }

    if ((*Ktab)[n].status == 3) {
        const float MAX_MATE_DIST = 90.0f;
        float min = MAX_MATE_DIST * MAX_MATE_DIST;
        float dx = 0.0f, dy = 0.0f;
        int i = -1;

        // Search only adjacent spatial grid cells (O(1) localized search)
        int gx = (int)(*Ktab)[n].x / CELL_SIZE;
        int gy = (int)(*Ktab)[n].y / CELL_SIZE;
        int minGx = std::max(0, gx - 3);
        int maxGx = std::min(GRID_COLS - 1, gx + 3);
        int minGy = std::max(0, gy - 3);
        int maxGy = std::min(GRID_ROWS - 1, gy + 3);

        for (int cy = minGy; cy <= maxGy; cy++) {
            for (int cx = minGx; cx <= maxGx; cx++) {
                const auto& cell = s_rabbitGrid[cy][cx];
                for (int m : cell) {
                    if (m != n && (*Ktab)[m].status == 3 && ((*Ktab)[n].plec != (*Ktab)[m].plec) && ((*Ktab)[m].wiek > wiek_dojrz)) {
                        float cdx = (*Ktab)[n].x - (*Ktab)[m].x;
                        float cdy = (*Ktab)[n].y - (*Ktab)[m].y;
                        float odl = cdx * cdx + cdy * cdy;
                        if (odl < min) {
                            min = odl;
                            i = m;
                        }
                    }
                }
            }
        }

        if (i >= 0) {
            min = sqrtf(min);
            dx = (*Ktab)[n].x - (*Ktab)[i].x;
            dy = (*Ktab)[n].y - (*Ktab)[i].y;
            if (min > 3.0f) {
                if (min > 0.0f) {
                    dx = vk * dx / min;
                    dy = vk * dy / min;
                }
            } else {
                dx = (float)(random(3) - 1);
                dy = (float)(random(3) - 1);
            }

            x = (*Ktab)[n].x - dx;
            y = (*Ktab)[n].y - dy;

            if ((min < 5.0f) && (Ktab->size() < 6000) && ((*Ktab)[n].ciaza < 0) && ((*Ktab)[n].plec == false)) {
                (*Ktab)[n].ciaza = dl_ciazy;
                if ((*Ktab)[n].plod == nullptr) (*Ktab)[n].plod = new PlodK();

                (*Ktab)[n].plod->wielkosc = ((*Ktab)[n].wielkosc + (*Ktab)[i].wielkosc) / 2.0f;
                (*Ktab)[n].plod->glod = ((*Ktab)[n].glod + (*Ktab)[i].glod) / 2.0f;
                (*Ktab)[n].plod->starving = ((*Ktab)[n].starving + (*Ktab)[i].starving) / 2.0f;
            }
        } else {
            // No mate in immediate range: wander gently and forage
            dx = (float)(random(3) - 1);
            dy = (float)(random(3) - 1);
            x = (*Ktab)[n].x - dx;
            y = (*Ktab)[n].y - dy;
        }
    }

    if (y < 2) y = 2;
    if (x < 2) x = 2;
    if (x > szer - 2) x = (float)(szer - 2);
    if (y > wys - 2) y = (float)(wys - 2);

    if (pole[(int)x][(int)y] >= 0) {
        (*Ktab)[n].x = x;
        (*Ktab)[n].y = y;

        if (pole[(int)x][(int)y] > 0) {
            (*Ktab)[n].pamiec_trawy[0] = (int)x;
            (*Ktab)[n].pamiec_trawy[1] = (int)y;
        }
    }

    if ((*Ktab)[n].ciaza == 0) {
        dodaj((*Ktab)[n].x, (*Ktab)[n].y, (int)((*Ktab)[n].zoladek /= 3.0f), n);
        (*Ktab)[n].zoladek /= 3.0f;
        (*Ktab)[n].ciaza = -1;
    }

    (*Ktab)[n].zoladek -= (*Ktab)[n].metabolizm;
    (*Ktab)[n].wiek++;
    if ((*Ktab)[n].ciaza >= 0) (*Ktab)[n].ciaza--;
}

void Kroliki::kill(int n) {
    if (n >= 0 && n < (int)Ktab->size()) {
        if ((*Ktab)[n].plod) {
            delete (*Ktab)[n].plod;
            (*Ktab)[n].plod = nullptr;
        }
        (*Ktab)[n] = (*Ktab)[Ktab->size() - 1];
        Ktab->pop_back();
    }
}
