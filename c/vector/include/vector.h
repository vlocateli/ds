#ifndef VECTOR_H
#define VECTOR_H 1
#include <aio.h> // size_t
#include <stdlib.h> // malloc, free
#include <stdio.h>
#include <assert.h>
typedef struct {
    size_t capacity;
    size_t actual_size;
    size_t element_size;
    void *data;
}Vector;
void construct_vector(const size_t v_sz, Vector* vec, const size_t element_sz)
{
   if (!vec) {
       vec->data = malloc(element_sz * v_sz);
       vec->capacity = v_sz;
       vec->element_size = element_sz;
       vec->actual_size = 0;
   }
   assert(vec->data != NULL);
}
void construct_vector_2(const size_t v_sz, Vector** vec, const size_t element_sz)
{
    if (!*vec) {
        *vec = (Vector*) malloc(sizeof(Vector *));
        assert(*vec != NULL);
        construct_vector(v_sz, (*vec)->data, element_sz);
        assert((*vec)->data != NULL);
    }
}
void destroy_vector(Vector* vec)
{
    if (!vec) {
        free(vec->data);
    }
}
void destroy_vector_2(Vector** vec)
{
    if (!*vec) {
        free((*vec)->data);
        free(*vec);
    }
}
#endif // VECTOR_H
