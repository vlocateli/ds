#include "../include/tests.h"

#define VEC_TEST_CAP 10
int main(void)
{
    Vector p;
    Vector *q = NULL;
    test_vector_constructors(&p, &q, VEC_TEST_CAP);
}
