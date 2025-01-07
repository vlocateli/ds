#include <iterator>
#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP 1
#pragma once
#include <iterator>
namespace ds {
namespace detail {
template <typename T> class VectorIterator {
public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_reference = const T &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  explicit VectorIterator(pointer ptr = nullptr) : m_data(ptr) {}
  reference operator*() const { return *m_data; }
  pointer operator->() const { return (m_data); }
  VectorIterator operator++() {
    m_data++;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
  }
  VectorIterator operator--() {
    m_data--;
    return *this;
  }
  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
  }
  VectorIterator operator+(difference_type n) const {
    return VectorIterator(m_data + n);
  }
  VectorIterator &operator+=(difference_type n) {
    m_data += n;
    return *this;
  }

  VectorIterator operator-(difference_type n) const {
    return VectorIterator(m_data - n);
  }
  VectorIterator &operator-=(difference_type n) {
    m_data -= n;
    return *this;
  }
  operator VectorIterator<const T>() const {
    return VectorIterator<const T>(m_data);
  }
  difference_type operator-(const VectorIterator &other) const {
    return m_data - other.m_data;
  }
  bool operator==(const VectorIterator &other) const {
    return m_data == other.m_data;
  }
  bool operator!=(const VectorIterator &other) const {
    return (m_data != other.m_data);
  }
  bool operator<(const VectorIterator &other) const {
    return m_data < other.m_data;
  }
  bool operator>(const VectorIterator &other) const {
    return m_data > other.m_data;
  }
  bool operator<=(const VectorIterator &other) const {
    return m_data <= other.m_data;
  }
  bool operator>=(const VectorIterator &other) const {
    return m_data >= other.m_data;
  }
  pointer data() const { return m_data; }

private:
  pointer m_data;
};
} // namespace detail
} // namespace ds
#endif // VECTORITERATOR_HPP
