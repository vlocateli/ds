#include <iostream>
#include "../include/stack.hpp"

int main()
{
    ds::Stack<size_t> s;
    s.push(2);
    s.push(3);
    std::cout << s << '\n';
    //s.pop();
    //std::cout << s << '\n';
}
