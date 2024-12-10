#ifndef STACK_HPP
#define STACK_HPP 1
#pragma once
#include "node.hpp"
#include <iostream>
#define DEBUG 1
#ifdef DEBUG
#include <assert.h>
#define DEBUG_PRINT(x)\
    std::cerr << #x << ": " << '\n';
#endif // DEBUG
namespace ds{
#ifdef STACK_SLL_IMPLEMENTATION
template<typename T>
class Stack : public ds::Node<T>{
    public:
        Stack();
        ~Stack();
        void push(const T& val);
        T pop();
        T& pop_ref();
        size_t size() const;
        T top() const;
        bool empty() const;
        Stack operator=(const Stack& other)
        {
            if (this == other) {
                return *this;
            }
            deallocate_stack();
            while (not empty()) {
               T pop_val = other.pop;
               push(pop_val);
            }
        }
        Stack (const Stack<T>& other)
            :  ds::Node<T>(),
               m_top{nullptr},
               m_size{other.m_size}
        {
            auto current = other.top();
            while (current != nullptr) {
                T current_value = current->value();
                push(current_value);
                current = current->next();
            }
        }

    private:
        ds::Node<T> *m_top;
        size_t       m_size;
        void deallocate_stack();
};
template<typename T>
Stack<T>::Stack()
    :
     m_top{nullptr},
     m_size{0}
{

}
template<typename T>
Stack<T>::~Stack()
{
   while (not empty()) {
        pop();
   }
}
// FIXME: check for size overflow
template<typename T>
void Stack<T>::push (const T& val)
{
    ds::Node<T>*  new_node;
    new_node = new ds::Node<T>(val);
    new_node->set_next(m_top);
    m_top = new_node;
    m_size++;
}
template<typename T>
void Stack<T>::deallocate_stack()
{
    while (not empty()) {
        pop();
    }
    m_top  = nullptr;
    m_size = 0;
}
template<typename T>
bool Stack<T>::empty () const
{
    return m_top == nullptr;
}
template<typename T>
T Stack<T>::pop ()
{
   if (empty()) {
    throw std::underflow_error("ERROR:Stack underflow");
    throw;
   }
   T pop_value = m_top->value();
   auto next_node = m_top->next();
   auto deleted_node = m_top;
   m_top = next_node;
   delete deleted_node;
   m_size--;
   return pop_value;
}
template<typename T>
size_t Stack<T>::size() const
{
    return m_size;
}
template<typename T>
T Stack<T>::top() const
{
    return m_top->value();
}
#endif // STACK_SLL_IMPLEMENTATION
} // ds

#endif // STACK_HPP
