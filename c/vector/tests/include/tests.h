#ifndef TESTS_H
#define TESTS_H 1
#pragma once
#include "../../include/vector.h"
void test_vector_constructors(Vector *p, Vector **q, const size_t cap)
{
   vector_create(p, cap);
   vector_create_2(q, cap);

}
#endif  // TESTS_H
