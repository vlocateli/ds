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
    : ptr_{ptr}
    {
    }

    reference operator*() const
    {
        return ptr_->value_ref();
    }

    pointer operator->() const
    {
        return &(ptr_->value());
    }

    Iterator& operator++()
    {
        ptr_ = ptr_->next();
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
        return ptr_ == other.ptr_;
    }

    bool operator!= (const Iterator& other) const
    {
        return ptr_ != other.ptr_;
    }
    SLLNode<T>* ptr() const
    {
        return ptr_;
    }
private:
    SLLNode<T>* ptr_;
};
} // detail
} // ds
#endif // SLLISTITERATOR_HPP
