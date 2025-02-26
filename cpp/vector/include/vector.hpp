#ifndef VECTOR_HPP
#define VECTOR_HPP 1
#pragma once
// TODO:
// 1) Clean up the project to C++11 std.
#define DEBUG 1
#ifdef DEBUG
#include <assert.h>
#define PRINT_DBG(q) std::cerr << #q << ":" << q << '\n';
#define PRINT_VEC\
    for (size_t i = 0; i < m_actual_size; i++) {\
        std::cerr << m_data[i] << ' ';\
    }\
    std::puts("");
#endif // DEBUG
#include "vectoriterator.hpp"
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string.h>
#include <utility>
#include <new>
#include <algorithm>
#include <memory>
namespace ds {
template <typename T, typename Allocator = std::allocator<T>> class Vector {
public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
  using iterator = ds::detail::VectorIterator<T>;
  using const_iterator   = const ds::detail::VectorIterator<T>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  // ctors
  Vector();
  explicit Vector(const Allocator& alloc); 
  Vector(const size_type  count, const Allocator& alloc = Allocator());
  Vector(const size_type  count, const T& value, const Allocator& alloc = Allocator());
  template<typename InputIt>
  Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
  Vector(const Vector& other );
  Vector(Vector&& other);
  Vector(const Vector& other, const Allocator& alloc); 
  Vector(Vector&& other, const Allocator& alloc);
  Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());
  
  ~Vector(); 
  void push_back(const T &);
  void push_back(T&&);
  void pop_back();
  template<typename ...Args>
  void emplace_back(Args&&... args);
  typename Vector<T,Allocator>::iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  void emplace_back(const T &);
  size_type erase(const T &);
  void erase_if(const size_type &);
  size_type capacity() const;
  size_type size() const;
  size_type max_capacity();
  void reserve(const size_type &new_cap);
  void resize(const size_type &new_size, const T &default_value = {});
  void clear();
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  reference at(const size_type pos);
  iterator insert(const_iterator pos, const T& value);
  void insert(const size_t, const T& value);
  bool empty() const;
  void shrink_to_fit();
  template <typename InputIt>
  void assign(InputIt first, InputIt last);
  void assign(const std::initializer_list<T> &ilist);
  void assign(const size_type &count, const T &value);
  reference operator[](size_type pos);
  const_reference operator[] (size_type pos) const;
  Vector& operator=(Vector&& other);
  iterator begin() { return iterator(m_data); };
  const_iterator begin() const { return iterator(m_data); }
  const_iterator end() const { return iterator(m_data + m_size); }
  iterator end() { return iterator(m_data + m_size); }
  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return end(); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const ds::detail::VectorIterator<T> crbegin() { return rbegin(); }
  const ds::detail::VectorIterator<T> crend() { return rend(); }
  void swap(Vector<T, Allocator>& other);
  const T *data() const noexcept;
  T* data() noexcept;
private: // Members
  pointer    m_data;
  size_type  m_capacity;
  size_type  m_size;
  Allocator allocator;
  void dealloc_data();
};

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector() : m_data{nullptr}, m_capacity{2}, 
                                 m_size{0}, allocator{Allocator()}
{
    try{
        m_data = allocator.allocate(m_capacity);
    } catch (std::bad_array_new_length& err) {
        std::cerr << "ERROR: No free memory available.";
        throw;
    }
}
template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const size_type count, const Allocator& alloc)
    : m_data{nullptr}, m_capacity{count * 2}, m_size{count},
      allocator{alloc}
{
  try {
    m_data = allocator.allocate(m_capacity);
  } catch (std::bad_array_new_length& err) {
    std::cerr << "ERROR: Could not allocate memory\n";
    exit(1);
  }

  for (size_type i = 0; i < m_size; i++) {
    m_data[i] = T();
  }
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_type count, T const& value, Allocator const&
                             alloc)
    :
        m_data{nullptr},
        m_capacity{count * 2},
        m_size{count},
        allocator{alloc}
{
    try{
        m_data = allocator.allocate(m_capacity);
    } catch(std::bad_array_new_length& err) {
        std::cerr << "ERROR: Could not allocate memory\n";
        exit(1);
    }
    for (size_type i = 0; i < count; i++) {
        m_data[i] = value;
    }
}
template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& other)
    :
        Vector(other.size())
{
    if (this == &other) {
        return;
    }
    auto other_it = other.cbegin();
    auto vector_it = begin();
    while (other_it != other.cend() && vector_it != end()) {
        *vector_it = *other_it;
        vector_it++, other_it++;
    }
    m_size = other.size();
}
template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other)
    :Vector(other.size())
{
    if (this == &other) {
        return;
    }

    *this = std::move(other);
    allocator.deallocate(other.m_data, other.m_capacity);
    other.m_data = nullptr;
    other.m_capacity = other.m_size = 0;
}
template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& other, const Allocator& alloc)
    :
     Vector(other.size(), alloc)
{
    if (this == &other) {
        return;
    }
    std::copy(other.begin(), other.end, m_data);
    m_size = other.size();
}
template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other, const Allocator& alloc)
    :
     
     Vector(other.size(), alloc)
{
    if (this == &other) {
        return;
    }

    *this = std::move(other);
    allocator.deallocate(other.m_data, other.m_capacity);
    other.m_capacity = other.m_size = 0;
    other.m_data = nullptr;
}
template <typename T, typename Allocator> 
Vector<T, Allocator>::~Vector() {
  allocator.deallocate(m_data, m_capacity);
  m_capacity = m_size = 0;
  m_data = nullptr;
}
template <typename T, typename Allocator> 
void Vector<T, Allocator>::push_back(const T &value) {
  try {
    if (m_size == m_capacity) {
      if (m_capacity == 0) {
        m_capacity = 2;
      } else {
        m_capacity *= 2;
      }
      auto new_data = allocator.allocate(m_capacity);
      std::copy(m_data, m_data + m_size, new_data);
      dealloc_data();
      m_data = new_data;
    }
    m_data[m_size] = value;
    m_size++;
  } catch (std::bad_array_new_length &err) {
    std::cerr << err.what() << '\n';
    throw;
  }
}

template <typename T, typename Allocator> 
size_t Vector<T, Allocator>::capacity() const { return m_capacity; }

template <typename T, typename Allocator> size_t Vector<T, Allocator>::size() const {
  return m_size;
}
template <typename T, typename Allocator> const T *Vector<T, Allocator>::data() const noexcept{ return m_data; }
template<typename T, typename Allocator> T *Vector<T, Allocator>::data() noexcept
{
    return m_data;
}
template <typename T, typename Allocator> void Vector<T, Allocator>::dealloc_data() { allocator.deallocate(m_data, m_capacity); }
template <typename T, typename Allocator> size_t Vector<T, Allocator>::max_capacity() {
  return std::numeric_limits<difference_type>::max();
}
template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init, const Allocator& alloc)
    : 
        Vector(init.size() * 2, alloc)
{
  m_data = allocator.allocate(m_capacity);
  std::size_t i = 0;
  for (const auto &data : init) {
    m_data[i] = data;
    i++;
  }
  PRINT_DBG(m_size);
  PRINT_DBG(init.size());
}
template <typename T, typename Allocator> const T& Vector<T, Allocator>::operator[](const std::size_t index) const {
  return m_data[index];
}
template<typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](const std::size_t index)
{
    return m_data[index];
}
template<typename T, typename Allocator>
Vector<T,Allocator>& Vector<T,Allocator>::operator=(Vector&& other)
{
    if (this == &other) {
        return *this;
    }

    m_data = std::move(other.m_data);
    m_size = std::move(other.m_size);
    m_capacity = std::move(other.m_capacity);
    return *this;
}
template<typename T, typename Allocator>
void Vector<T, Allocator>::push_back(T&& value)
{
    try{
        if (m_size == m_capacity) {
            m_capacity *= 2;
        }
    reserve(m_capacity);
    m_data[m_size] = std::move(value);
    m_size++;

    }catch(std::bad_alloc &err) {
        std::cerr << err.what() << '\n';
    }
}
template <typename T, typename Allocator> void Vector<T, Allocator>::reserve(const size_type &new_cap) {
  try{
      if (new_cap < m_capacity) {
          return;
      }
      else if (new_cap > m_capacity || m_data == nullptr) {
        auto new_data = allocator.allocate(new_cap, m_data);
        std::move(m_data, m_data + m_size, new_data);
        dealloc_data();
        m_data = new_data;
        m_capacity = new_cap;
      }
  } catch(std::bad_array_new_length& err) {
    std::cerr << "ERROR: No free memory available\n";
    throw;
  }
}
template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(const size_type &new_size, const T &default_value) {
  if (new_size > max_capacity()) {
    throw std::length_error(
        "ERROR: New capacity would exceed maximum size for type T\n");
    throw;
  }
  if (new_size >= m_capacity) {
    reserve(new_size);
    std::fill(m_data + m_size, m_data + new_size, default_value);
  }

  if (new_size < m_capacity) {
    reserve(new_size);
  }
}
template <typename T, typename Allocator> T &Vector<T, Allocator>::front() { return m_data[0]; }
template <typename T, typename Allocator> const T &Vector<T, Allocator>::front() const { return m_data[0]; }
template <typename T, typename Allocator> T &Vector<T, Allocator>::back() { return m_data[m_size]; }
template <typename T, typename Allocator> const T &Vector<T, Allocator>::back() const {
  return m_data[m_size];
}
template <typename T, typename Allocator> T &Vector<T, Allocator>::at(const size_t pos) {
  if (pos < m_size) {
    return *(m_data + pos);
  }
  throw std::out_of_range("ERROR: Position out of range\n");
  throw;
}
template <typename T, typename Allocator> void Vector<T, Allocator>::clear() {
  dealloc_data();
  m_data = nullptr;
  m_capacity = m_size = 0;
}
template <typename T, typename Allocator>
void Vector<T, Allocator>::assign(const size_t &count, const T &value) {
  resize(count);
  std::fill(begin(), end(), value);
}
template<typename T, typename Allocator>
detail::VectorIterator<T> Vector<T, Allocator>::insert(const_iterator pos, const T& value)
{
    auto distance = std::distance(this->cbegin(), pos);
    if (m_capacity == m_size) {
        const size_type new_cap = m_capacity * 2;
        resize(new_cap);
    }
    //std::rotate(begin() + distance, end(), end() + 1);
    for (ssize_t i = static_cast<ssize_t>(m_size) - 1; i >= distance; i--) {
        m_data[i + 1] = m_data[i];
    }
    m_data[distance] = value;
    m_size++;
    return begin() + distance;
}
template<typename T, typename Allocator>
template<typename ...Args>
void Vector<T, Allocator>::emplace_back(Args&& ...args)
{
    if (m_size == m_capacity) {
        m_capacity *= 2;
        reserve(m_capacity);
    }
    assert(m_data != nullptr);
    new (&m_data[m_size]) T(std::forward<Args>(args) ...);
    m_size++;
}
template<typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const
{
    return m_size == 0;
}
template<typename T, typename Allocator>
void Vector<T, Allocator>::shrink_to_fit()
{
    if (m_capacity > m_size) {
        resize(m_size);
    }
}
template<typename T, typename Allocator>
void Vector<T, Allocator>::pop_back()
{
    m_size--;
    resize(m_size);
}
template<typename T, typename Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator pos)
{
    if (pos == end()) {
        return end();
    }
    auto dist = std::distance(begin(), pos);
    m_data[dist].~T();
    std::rotate(begin(), pos, end());
    return pos;
}
template<typename T, typename Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator first, const_iterator last)
{
   if (last == cend()) {
       return end();
   }

   auto it = first;
   while (it != last) {
       erase(it);
       it++;
   }

   return last + 1;
}
template<typename T, typename Allocator>
void Vector<T, Allocator>::swap(Vector& other)
{
   assert(false and "Unimplemented"); 
}
template<typename T, typename Allocator>
template<typename InputIt>
void Vector<T, Allocator>::assign(InputIt first, InputIt last)
{
    auto distance = last - first;
    reserve(distance);
    auto it = begin();
    while (first != last) {
        *it = *first;
        first++;
    }
}
} // namespace ds
#endif // VECTOR_HPP
