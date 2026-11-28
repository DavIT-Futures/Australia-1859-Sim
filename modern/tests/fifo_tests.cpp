#include "kolejka.h"

namespace {

int test_fifo_preserves_insertion_order_and_size() {
    FIFO queue;
    if (!queue.empty() || queue.size() != 0) {
        return 1;
    }

    queue.push(10, 20, 1);
    queue.push(30, 40, 2);
    if (queue.empty() || queue.size() != 2) {
        return 2;
    }

    int x = 0, y = 0, c = 0;
    queue.pop(x, y, c);
    if (x != 10 || y != 20 || c != 1 || queue.size() != 1) {
        return 3;
    }

    queue.pop(x, y, c);
    if (x != 30 || y != 40 || c != 2 || !queue.empty() || queue.size() != 0) {
        return 4;
    }

    return 0;
}

int test_fifo_clear_empties_queue_and_allows_reuse() {
    FIFO queue;
    queue.push(1, 2, 3);
    queue.push(4, 5, 6);
    queue.clear();

    if (!queue.empty() || queue.size() != 0) {
        return 10;
    }

    int x = 99, y = 98, c = 97;
    queue.pop(x, y, c);
    if (x != 99 || y != 98 || c != 97 || !queue.empty() || queue.size() != 0) {
        return 11;
    }

    queue.push(7, 8, 9);
    if (queue.empty() || queue.size() != 1) {
        return 12;
    }

    queue.pop(x, y, c);
    if (x != 7 || y != 8 || c != 9 || !queue.empty() || queue.size() != 0) {
        return 13;
    }

    return 0;
}

int test_fifo_handles_interleaved_drain_and_refill_cycles() {
    FIFO queue;
    queue.push(-5, 0, 11);
    int x = 0, y = 0, c = 0;
    queue.pop(x, y, c);
    if (x != -5 || y != 0 || c != 11 || !queue.empty() || queue.size() != 0) {
        return 20;
    }

    queue.push(100, -200, 3);
    queue.push(400, 500, -4);
    if (queue.empty() || queue.size() != 2) {
        return 21;
    }

    queue.pop(x, y, c);
    if (x != 100 || y != -200 || c != 3 || queue.size() != 1) {
        return 22;
    }

    queue.pop(x, y, c);
    if (x != 400 || y != 500 || c != -4 || !queue.empty() || queue.size() != 0) {
        return 23;
    }

    return 0;
}

} // namespace

int main() {
    if (int rc = test_fifo_preserves_insertion_order_and_size(); rc != 0) {
        return rc;
    }
    if (int rc = test_fifo_clear_empties_queue_and_allows_reuse(); rc != 0) {
        return rc;
    }
    return test_fifo_handles_interleaved_drain_and_refill_cycles();
}
