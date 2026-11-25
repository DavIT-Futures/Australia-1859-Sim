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

} // namespace

int main() {
    return test_fifo_preserves_insertion_order_and_size();
}
