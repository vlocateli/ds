#include "../include/tests.hpp"

int main() {
  if (test::test_constructors() and test::test_push_back() and
      test::test_capacity() and test::test_actual_size() and
      test::test_data() and test::test_max_capacity() and test::test_erase() and
      test::iterator::test_begin_end_iter() and
      test::iterator::test_rbegin_rend() and test::test_reserve() and
      test::test_resize() and test::test_at() and test::test_clear() and
      test::test_assign()) {
    std::cout << "All tests passed\n";
  } else {
    std::cerr << "oops\n";
  }
}
