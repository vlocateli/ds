#include "../include/sllist.hpp"
#include "../include/timer.hpp"
int main () {
    ds::LinkedList<size_t> list_1;

    for (size_t i = 1; i < 10; i++) {
        list_1.push_back(i);
    }
    ds::LinkedList<size_t> list_2(list_1);
    std::cout << list_2 << '\n';
    return 0;
}

