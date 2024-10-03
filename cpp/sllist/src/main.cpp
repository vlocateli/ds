#include "../include/sllist.hpp"
int main () {
    ds::LinkedList<size_t> list_1;

    for (size_t i = 1; i < 10; i++) {
        list_1.push_back(i);
    }
    std::cout << list_1 << '\n';
    return 0;
}

