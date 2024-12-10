#include "../include/test.hpp"

int main()
{
    if (test::test_constructor() and
        test::test_push_op() and
        test::test_size() and
        test::test_pop_op() and
        test::test_top_op()){
        std::cout << "All tests passed\n";
    }
}
