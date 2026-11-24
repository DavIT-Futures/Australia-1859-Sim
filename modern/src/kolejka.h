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
    std::size_t count;

public:
    FIFO() : head(nullptr), tail(nullptr), count(0) {}

    // Non-copyable to prevent shallow-copy double-free of linked-list nodes.
    FIFO(const FIFO&) = delete;
    FIFO& operator=(const FIFO&) = delete;

    ~FIFO() {
        clear();
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
        ++count;
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
            --count;
        }
    }

    /// Removes and deallocates all queued elements.
    void clear() {
        int x, y, c;
        while (!empty()) {
            pop(x, y, c);
        }
    }

    /// Returns the number of elements currently stored in the queue.
    std::size_t size() const {
        return count;
    }

    bool empty() const {
        return head == nullptr;
    }
};

#endif // KOLEJKA_H
