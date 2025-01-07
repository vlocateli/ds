#include "../include/vector.h"


int main()
{
    Vector p, *q;
    const size_t sz = 1024;
    construct_vector(sz, &p, sizeof(int));
    construct_vector_2(sz, &q, sizeof(int));
    for (size_t i = 0; i < sz; i++) {
        p.data[i] = i;
    }
    for (size_t i = 0; i < sz; i++) {
        printf("%i ", p.data[i]);
    }

}
