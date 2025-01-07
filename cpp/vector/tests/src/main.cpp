#include "../include/tests.hpp"

int main() {
    if (!test::test_constructors()) {
        std::cerr << "Constructors test failed\n";
    }

    if (!test::test_push_back()) {
        std::cerr << "push_back test failed\n";
    }

    if (!test::test_emplace_back()) {
        std::cerr << "emplace_back test failed\n"; 
    }

    if (!test::test_reserve()) {
        std::cerr << "reserve() test failed\n";
    }
    
    if(!test::test_insert()) {
        std::cerr << "insert() test failed\n";
    }

    if(!test::test_empty()) {
        std::cerr << "empty() test failed\n";
    }
    
    if(!test::test_pop_back()) {
        std::cerr << "pop_back() test failed\n";
    }
    test::test_erase();
}
