#ifndef TEST_HPP
#define TEST_HPP
#pragma once
#define STACK_SLL_IMPLEMENTATION
#include "../../include/stack.hpp"
#include "../../include/stackiterator.hpp"
namespace test{
   bool test_constructor();
   bool test_push_op();
   bool test_pop_op();
   bool test_size();
   bool test_top_op();

}
#endif // TEST_HPP
