#ifndef TESTS_HPP
#define TESTS_HPP 1
#pragma once
#include "../../include/vector.hpp"
#include "../../include/vectoriterator.hpp"
#include <limits>
/*
 * TODO:
 *      Refactor this crap
 */
template <typename Q>
std::ostream &operator<<(std::ostream &stream, const ds::Vector<Q> &arr) {

  for (size_t i = 0; i < arr.actual_size(); i++) {
    stream << arr.data()[i] << ' ';
  }
  return stream;
}
namespace test{
    bool test_constructors();
    bool test_push_back();
    bool test_emplace_back();
    bool test_capacity();
    bool test_actual_size();
    bool test_max_capacity();
    bool test_reserve();
    bool test_resize();
    bool test_clear();
    bool test_front();
    bool test_back();
    bool test_at();
    bool test_assign();
    bool test_operator_overloading();
    bool test_begin();
    bool test_end();
    bool test_data();
    bool test_insert();
    bool test_empty();
    bool test_pop_back();
    bool test_erase();
}
#endif // TESTS_HPP
