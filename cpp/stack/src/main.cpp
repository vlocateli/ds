#include "../include/stack.hpp"

int main()
{
    ds::Stack<int32_t> p;

    for (auto i = 0; i < 10; i++) {
        p.push(i);
    }
    DEBUG_PRINT(p);
}
