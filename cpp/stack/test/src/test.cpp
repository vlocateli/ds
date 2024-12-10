#include "../include/test.hpp"

namespace test{
    using namespace ds;
    bool test_constructor()
    {
        Stack<int> s;
        assert(s.empty());
        return true;
    }
    bool test_push_op()
    {
        Stack<int> s;
        for (int i = 0; i < 10; i++) {
            s.push(i);
        }
        assert(not s.empty());
        return true;
    }
    bool test_pop_op()
    {
        Stack<int> s;
        for (int i = 0; i < 10; i++) {
            s.push(i);
        }
        auto ret = s.pop();
        assert(ret == 9);
        return true;
    }
    bool test_size()
    {
        Stack<int> s;
        for (int i = 0; i < 10; i++) {
            s.push(i);
        }
        assert(s.size() == 10);
        Stack<int> p;
        assert(p.size() == 0);
        return true;
    }
    bool test_top_op()
    {
        Stack<int> s;
        for (int i = 0; i < 10; i++) {
            s.push(i);
        }
        assert(s.top() == 9);
        return true;
    }
} // test 
