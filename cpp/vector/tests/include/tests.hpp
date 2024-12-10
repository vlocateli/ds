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
namespace init {
#define KIB 1024
#define MIB 1024 * KIB
#define GIB 1024 * MIB
#define VEC_MAX_CAP KIB >> 4
using namespace ds;
Vector<unsigned> u_v(VEC_MAX_CAP);
Vector<float> spf_v(VEC_MAX_CAP);
Vector<char> c_v(VEC_MAX_CAP);
Vector<int> i_v(VEC_MAX_CAP);
Vector<double> dpf_v(VEC_MAX_CAP);
} // namespace init
namespace test {
using namespace ds;
bool test_constructors();
bool test_push_back();
bool test_capacity();
bool test_actual_size();
bool test_data();
bool test_erase();
bool test_max_capacity();
bool test_constructors() {
  Vector<unsigned> p;
  Vector<int32_t> q(1024);
  assert(p.capacity() == 0);
  assert(q.capacity() == 1024);
  return true;
}
bool test_push_back() {
  Vector<unsigned> p;
  std::size_t cap = 10 * 1024;
  for (size_t i = 0; i < cap; i++) {
    p.push_back(i);
  }
  assert(p.actual_size() == (cap));
  return true;
}
bool test_capacity() {
  Vector<unsigned> p;
  assert(p.capacity() == 0);
  Vector<unsigned> v(1024);
  assert(v.capacity() == 1024);
  return true;
}
bool test_actual_size() {
  Vector<unsigned> q;
  assert(q.actual_size() == 0);
  Vector<unsigned> v(1024);
  assert(v.actual_size() == 0 and v.capacity() == 1024);
  return true;
}
bool test_data() {
  Vector<char> words;
  assert(words.data() == nullptr);
  Vector<unsigned> nums(1024);
  assert(nums.data() != nullptr);
  return true;
}
bool test_erase() {
  using namespace init;
  for (std::size_t i = 0; i < i_v.capacity() >> 4; i++) {
    i_v.push_back(static_cast<int>(0));
  }
  for (std::size_t j = i_v.capacity() >> 4; j < i_v.capacity(); j++) {
    i_v.push_back(static_cast<int>(1));
  }

  auto ret = i_v.erase(0);
  assert(ret == 4);
  ret = i_v.erase(8);
  assert(ret == 0);
  ret = i_v.erase(1);
  assert(ret == 60);
  ret = c_v.erase('a');
  assert(ret == 0);
  assert(c_v.actual_size() == 0);
  return true;
}
bool test_max_capacity() {
  Vector<unsigned> p;
  assert(p.max_capacity() == std::numeric_limits<std::ptrdiff_t>::max());
  return true;
}
bool test_reserve();
bool test_reserve() {
  Vector<int> v;
  v.reserve(1 * KIB);
  assert(v.capacity() == (1 * KIB));
  Vector<float> p;
  v.reserve(0 * KIB);
  assert(v.capacity() == 0);
  return true;
}
bool test_resize();
bool test_resize() {
  Vector<int> v{1, 2, 3, 4, 5, 6};
  v.resize(5);
  assert(v.capacity() == 5);
  v.resize(20);
  assert(v.capacity() == 20);
  v.resize(0);
  return true;
}
bool test_front();
bool test_front() {
  Vector<int> v{1, 2, 3};
  assert(v.front() == 1);
  const Vector<long> p{1L, 2L, 3L};
  assert(v.front() == 1L);
  return true;
}
bool test_back();
bool test_back() {
  Vector<int> v{1, 2, 3};
  assert(v.back() == 3);
  const Vector<long> p{1L, 2L, 3L};
  assert(p.back() == 3L);
  return true;
}
bool test_at();
bool test_at() {
  Vector<int> v{1, 2, 3};
  assert(v.at(0) == 1 and v.at(1) == 2 and v.at(2) == 3);
  return true;
}
bool test_clear();
bool test_clear() {
  Vector<int> v{1, 2, 3, 4, 5};
  assert(v.capacity() == 5);
  v.clear();
  assert(v.capacity() == 0);
  return true;
}
bool test_assign();
bool test_assign() {
  Vector<int> v;
  v.assign(10, 1);
  assert(v.capacity() == 10);
  Vector<int> p{1, 2, 3, 4, 5};
  Vector<int> q;
  auto it_p_begin = p.begin();
  auto it_p_end = p.end();
  q.assign(it_p_begin, it_p_end);
  assert(q.capacity() == p.capacity());
  return true;
}
} // namespace test
namespace test::iterator {
bool test_begin_end_iter();
bool test_begin_end_iter() {
  Vector<int> v(VEC_MAX_CAP);
  for (std::size_t i = 0; i < VEC_MAX_CAP; i++) {
    v.push_back(static_cast<int>(i));
  }
  Vector<int> expected = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
                          13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                          26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                          39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
                          52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
  auto iv_iter = v.begin();
  auto expected_iter = expected.begin();
  while (iv_iter != v.end() and expected_iter != expected.end()) {
    if (*iv_iter != *expected_iter) {
      return false;
    }
    iv_iter++, expected_iter++;
  }
  return true;
}
bool test_rbegin_rend();
bool test_rbegin_rend() {
  Vector<int> p(10);
  for (std::size_t i = 0; i < 10; i++) {
    p.push_back(static_cast<int>(i));
  }
  auto r_iter = p.rbegin();
  assert(*r_iter == 9);
  Vector<int> result;
  std::size_t cap = 0;
  while (r_iter != p.rend()) {
    result.push_back(*r_iter);
    r_iter++;
    cap++;
  }
  Vector<int> expected = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  for (std::size_t i = 0; i < expected.capacity(); i++) {
    if (result[i] != expected[i]) {
      return false;
    }
  }
  return true;
}
bool test_cbegin_cend();
bool test_cbegin_cend() {
  const auto iv_iter = init::i_v.cbegin();
  assert(iv_iter == init::i_v.begin());
  return true;
}
} // namespace test::iterator
#endif // TESTS_HPP
