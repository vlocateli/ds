#include "../include/tests.hpp"
struct Foo{
   int field_1;
   float field_2;
   Foo()
   :
        field_1{},
        field_2{}
   {
   }
   Foo(const int f1, const float f2)
    :
        field_1{f1},
        field_2{f2}
   {

   }
   ~Foo() = default;

};

namespace test{
    using namespace ds;
    bool test_constructors()
    {
        Vector<int> v; 
        Vector<int> p(1024);
        Vector<int> q{1,2,3,4};
        assert(v.actual_size() == 0);
        assert(p.actual_size() == 0);
        assert(q.actual_size() == 4);
        return true;
    }

    bool test_push_back()
    {
        Vector<unsigned int> v;
        for (unsigned int i = 0; i < 1024; i++) {
            v.push_back(i, 2);
        }
        assert(v.actual_size() == 1024);

        Vector<Foo> p(10);
        Foo f(10, 5.5);
        p.push_back(f);
        assert(p.actual_size() == 1);
        return true;
    }
    bool test_reserve()
    {
        Vector<int> v;
        v.reserve(1024);
        assert(v.capacity() == 1024);

        return true;
    }
    bool test_emplace_back()
    {
        Foo f;
        Foo b;
        Vector<Foo> v;
        v.emplace_back(f);
        v.emplace_back(b);
        assert(v.actual_size() == 2);
        return true;
    }
    bool test_insert()
    {
       Vector<int> v{1,2,3,4};
       auto it = v.begin();
       v.insert(it + 0, 5);
       assert(v.at(0) == 5);
       it = v.begin();
       v.insert(it + 5, 6);
       assert(v.at(5) == 6);
       it = v.begin();
       v.insert(it + 3, 8);
       assert(v.at(3) == 8);
      return true; 
    }
    bool test_empty()
    {
        Vector<int> v;
        assert(v.empty());
        Vector<float> p {1.0f};
        assert(!p.empty());
        return true;
    }
    bool test_pop_back()
    {
        Vector<int> v{1,2,3};
        while(not v.empty()) {
            v.pop_back();
        }
        assert(v.empty());
        return true;
    }
    bool test_erase()
    {
        Vector<int> v{1,2,3,5,6,7,8};
        v.erase(v.begin() + 1);
        v.erase(v.begin() + 1, v.begin() + 4);
        return true;
    }

}

