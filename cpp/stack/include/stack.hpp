#ifndef STACK_HPP
#define STACK_HPP 1
#pragma once
#include <iostream>
#include "node.hpp"
#define DEBUG 1
#ifdef DEBUG
#include <assert.h>
#include <iostream>
#define DEBUG_PRINT(x)\
    std::cerr << #x << ": " << '\n';
#endif // DEBUG
namespace ds{
template<typename T>
class Stack : public ds::Node<T>{
    public:
        Stack();
        ~Stack();
        void push(const T& val);
        T pop();
        T& pop_ref();
        size_t size() const;
        ds::Node<T>* top() const;
        bool is_empty() const;
        Stack operator=(const Stack& other)
        {
            if (this == other) {
                return this;
            }
            deallocate_stack();
            while (not is_empty()) {
               T pop_val = other.pop;
               push(pop_val);
            }
        }
        Stack (const Stack<T>& other)
            : m_size{other.m_size},
              m_top{nullptr}
        {
            auto tmp = other;
            while (not is_empty(tmp)) {
                auto pop_value = tmp.pop();
                push(pop_value);
            }
        }
        friend std::ostream& operator<< (std::ostream& stream, const ds::Stack<T> &s)
        {
            Stack<T> tmp = s;
            while (! tmp.is_empty()) {
                stream << tmp.pop() << ' ';
            }

            return stream;
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
   while (not is_empty()) {
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
    while (not is_empty()) {
        pop();
    }
    m_top  = nullptr;
    m_size = 0;
}
template<typename T>
bool Stack<T>::is_empty () const
{
    return m_size == 0;
}
template<typename T>
T Stack<T>::pop ()
{
   if (is_empty()) {
    throw std::underflow_error("Stack underflow occured. \
            Tried to pop on a empty stack.");
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
ds::Node<T>* Stack<T>::top() const
{
    return m_top;
}
} // ds

#endif // STACK_HPP
