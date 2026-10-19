#ifndef KOLEJKA_H
#define KOLEJKA_H

#include <cstddef>

// FIFO queue used for BFS terrain generation (waves, land heights, bays, smoothing)
class FIFO {
private:
    struct TEl {
        int x, y, c;
        TEl* nast;
    };

    TEl* head;
    TEl* tail;

public:
    FIFO() : head(nullptr), tail(nullptr) {}

    ~FIFO() {
        int x, y, c;
        while (!empty()) {
            pop(x, y, c);
        }
    }

    void push(int nx, int ny, int nc) {
        TEl* el = new TEl;
        el->x = nx;
        el->y = ny;
        el->c = nc;
        el->nast = nullptr;

        if (head == nullptr) {
            head = tail = el;
        } else {
            tail->nast = el;
            tail = el;
        }
    }

    void pop(int& nx, int& ny, int& nc) {
        if (head != nullptr) {
            nx = head->x;
            ny = head->y;
            nc = head->c;
            TEl* tmp = head;
            head = head->nast;
            if (head == nullptr) tail = nullptr;
            delete tmp;
        }
    }

    bool empty() const {
        return head == nullptr;
    }
};

#endif // KOLEJKA_H
