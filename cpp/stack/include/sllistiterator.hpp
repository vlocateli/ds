#ifndef SLLISTITERATOR_HPP
#define SLLISTITERATOR_HPP
#include <cstddef>
#pragma once
#include <iterator>
#include "node.hpp"
namespace ds{
namespace detail{
template<typename T>
class Iterator{
public:
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using const_reference   = const T&;
    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    explicit Iterator(SLLNode<T>* ptr = nullptr)
    : m_ptr{ptr}
    {
    }

    reference operator*() const
    {
        return m_ptr->value_ref();
    }

    pointer operator->() const
    {
        return &(m_ptr->value());
    }

    Iterator& operator++()
    {
        m_ptr = m_ptr->next();
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator== (const Iterator& other) const
    {
        return m_ptr == other.m_ptr;
    }

    bool operator!= (const Iterator& other) const
    {
        return m_ptr != other.m_ptr;
    }
    SLLNode<T>* ptr() const
    {
        return m_ptr;
    }
private:
    SLLNode<T>* m_ptr;
};
} // detail
} // ds
#endif // SLLISTITERATOR_HPP
