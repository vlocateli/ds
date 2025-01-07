#ifndef VECTOR_H
#define VECTOR_H
#pragma once
#include <stddef.h>
#include <stdlib.h>
typedef struct vector{
    void *m_data;
    size_t m_size;
    size_t m_capacity;
}Vector;
void vector_create(Vector* v, const size_t size)
{
    v->m_data = malloc(sizeof(void *) * size);
    v->m_size = size;
}
void vector_create_2(Vector** v, const size_t size)
{
    if (!(*v)) {
        (*v) =  malloc(sizeof(Vector));
    }
    (*v)->m_data = malloc(sizeof(void *) * size);
    (*v)->m_size = size;
}
void vector_create_empty(Vector* v, const size_t size)
{
    v->m_data = NULL; v->m_size = 0;
}
void vector_create_empty_2(Vector** v, const size_t size)
{
    if (!(*v)) {
        (*v) = malloc(sizeof(Vector));
    }
    (*v)->m_data = NULL;
    (*v)->m_size = size;
}
#endif // VECTOR_H
