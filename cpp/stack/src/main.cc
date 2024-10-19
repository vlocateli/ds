#include "../include/list.hh"
#include <iostream>
int main() {
  List<size_t> list(10);
  list.insert_end(20);
  //list.insert_end(30);
  std::cout << list << '\n';

  return 0;
}
