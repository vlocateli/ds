#include "../include/sllist.hpp"
int main () {
    ds::LinkedList<size_t> list_1;
    for (size_t i = 1; i < 10; i++) {
        list_1.push_back(i);
    }
    std::cout << list_1 << '\n';
    auto max = list_1.maximum();
    std::cout << max << '\n';
    auto min = list_1.minimum();
    std::cout << min << '\n';
    auto search_res = list_1.search(9);
    std::cout << *search_res << '\n';
    auto list_p = std::move(list_1);
    auto list_q(list_p);
    std::cout << "list_p (after move): " << list_p << '\n';
    std::cout << "list_q (after copy): " << list_q << '\n';
    list_q.push_back(100);
    std::cout << "list_p : " << list_p << '\n';
    std::cout << "list_q : " << list_q << '\n';
    std::cout << list_q.pop_back() << '\n';
    DEBUG_PRINT(list_q.minimum());
    DEBUG_PRINT(list_q.maximum());
    auto it_begin = list_q.begin();
    list_q.insert_after(it_begin, 10);
    ds::LinkedList<size_t> list_v;
    DEBUG_PRINT(list_q);
    list_q.push_front(0);
    DEBUG_PRINT(list_q);
    list_v.push_front(0);
    DEBUG_PRINT(list_v);
    list_q.reverse();
    DEBUG_PRINT(list_q);
    return 0;
}

