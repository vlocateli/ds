#ifndef VECTOR_HPP
#define VECTOR_HPP 1
#pragma once
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
namespace ds {
template <typename T> class Vector {
public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_reference = const T &;
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using iterator = ds::detail::VectorIterator<T>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_iterator   = const ds::detail::VectorIterator<T>;
  Vector();
  ~Vector();
  Vector(const size_type &);
  Vector(const std::initializer_list<T> &);
  Vector(Vector &);
  void push_back(const T &);
  void push_back(const T &, const size_type &);
  void push_back(T&&);
  void pop_back();
  template<typename ...Args>
  void emplace_back(Args&&... args);
  typename Vector<T>::iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  void emplace_back(const T &);
  size_type erase(const T &);
  void erase_if(const size_type &);
  size_type capacity() const;
  size_type actual_size() const;
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
  T &operator[](const size_type index);
  const T &operator[](const size_type index) const;
  iterator begin() { return iterator(m_data); }
  iterator end() { return iterator(m_data + m_actual_size); }
  const ds::detail::VectorIterator<T> cbegin() { return begin(); }
  const ds::detail::VectorIterator<T> cend() { return end(); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const ds::detail::VectorIterator<T> crbegin() { return rbegin(); }
  const ds::detail::VectorIterator<T> crend() { return rend(); }
  const T *data() const noexcept;
  T* data() noexcept;
private:
  T *m_data;
  size_t m_capacity;
  size_t m_actual_size;
  void dealloc_data();
};

template <typename T>
Vector<T>::Vector() : m_data{nullptr}, m_capacity{2}, m_actual_size{0} 
{
    try{
        m_data = new T[m_capacity];
    } catch (std::bad_alloc& err) {
        std::cerr << "ERROR: No free memory available.";
        throw;
    }
}

template <typename T> Vector<T>::~Vector() {
  delete[] m_data;
  m_capacity = m_actual_size = 0;
}

template <typename T>
Vector<T>::Vector(const size_t &size)
    : m_data{nullptr}, m_capacity{size}, m_actual_size{} {
  try {
    m_data = new T[m_capacity];
  } catch (std::bad_alloc &err) {
    std::cerr << "ERROR: Could not allocate memory\n";
    exit(1);
  }
}

template <typename T> void Vector<T>::push_back(const T &value) {
  try {
    const auto cache_line_size = std::hardware_destructive_interference_size; 
    const auto type_size = sizeof(T);
    std::size_t elements_per_cache_line = cache_line_size / type_size;
    if (m_actual_size == m_capacity) {
      if (m_capacity == 0) {
        m_capacity = elements_per_cache_line;
      } else {
        m_capacity *= elements_per_cache_line;
      }
      auto new_data = new T[m_capacity];
      if (new_data != nullptr) {
        std::copy(m_data, m_data + m_actual_size, new_data);
        dealloc_data();
      }
      m_data = new_data;
    }
    m_data[m_actual_size] = value;
    m_actual_size++;
  } catch (std::bad_alloc &err) {
    std::cerr << err.what() << '\n';
    throw;
  }
}

template <typename T> size_t Vector<T>::capacity() const { return m_capacity; }

template <typename T> size_t Vector<T>::actual_size() const {
  return m_actual_size;
}
template <typename T> const T *Vector<T>::data() const noexcept{ return m_data; }
template<typename T> T *Vector<T>::data() noexcept
{
    return m_data;
}
// TODO: Throw exception
template <typename T> void Vector<T>::dealloc_data() { delete[] m_data; }
template <typename T> size_t Vector<T>::max_capacity() {
  return std::numeric_limits<difference_type>::max();
}
template <typename T>
Vector<T>::Vector(const std::initializer_list<T> &init_list)
    : m_capacity{init_list.size()}, m_actual_size{init_list.size()} {
  m_data = new T[m_capacity];
  std::size_t i = 0;
  for (const auto &data : init_list) {
    m_data[i] = data;
    i++;
  }
}
template <typename T> const T& Vector<T>::operator[](const std::size_t index) const {
  return m_data[index];
}
template<typename T>
T& Vector<T>::operator[](const std::size_t index)
{
    return m_data[index];
}
template <typename T>
void Vector<T>::push_back(const T &value, const size_t &alloc_factor) {
  try {
    if (m_actual_size == m_capacity) {
        m_capacity *= alloc_factor;
      }
      auto new_data = new T[m_capacity];
      if (new_data != nullptr) {
        std::copy(m_data, m_data + m_actual_size, new_data);
        dealloc_data();
      }
    m_data = new_data;
    m_data[m_actual_size] = value;
    m_actual_size++;
  } catch (std::bad_alloc &err) {
    std::cerr << err.what() << '\n';
    throw;
  }
}
template<typename T>
void Vector<T>::push_back(T&& value)
{
    try{
        if (m_actual_size == m_capacity) {
            m_capacity *= 2;
        }
    reserve(m_capacity);
    m_data[m_actual_size] = std::move(value);
    m_actual_size++;

    }catch(std::bad_alloc &err) {
        std::cerr << err.what() << '\n';
    }
}
template <typename T> void Vector<T>::reserve(const size_type &new_cap) {
  try{
      if (new_cap < m_capacity) {
          return;
      }
      else if (new_cap > m_capacity || m_data == nullptr) {
        T *new_data = new T[new_cap];
        std::move(m_data, m_data + m_actual_size, new_data);
        dealloc_data();
        m_data = new_data;
        m_capacity = new_cap;
      }
  } catch(std::bad_alloc& err) {
    std::cerr << "ERROR: No free memory available\n";
    throw;
  }
}
template <typename T>
void Vector<T>::resize(const size_type &new_size, const T &default_value) {
  if (new_size > max_capacity()) {
    throw std::length_error(
        "ERROR: New capacity would exceed maximum size for type T\n");
    throw;
  }
  if (new_size >= m_capacity) {
    reserve(new_size);
    std::fill(m_data + m_actual_size, m_data + new_size, default_value);
  }

  if (new_size < m_capacity) {
    reserve(new_size);
  }
}
template <typename T> T &Vector<T>::front() { return m_data[0]; }
template <typename T> const T &Vector<T>::front() const { return m_data[0]; }
template <typename T> T &Vector<T>::back() { return m_data[m_actual_size]; }
template <typename T> const T &Vector<T>::back() const {
  return m_data[m_actual_size];
}
template <typename T> T &Vector<T>::at(const size_t pos) {
  if (pos < m_actual_size) {
    return *(m_data + pos);
  }
  throw std::out_of_range("ERROR: Position out of range\n");
  throw;
}
template <typename T> void Vector<T>::clear() {
  dealloc_data();
  m_data = nullptr;
  m_capacity = m_actual_size = 0;
}
template <typename T>
void Vector<T>::assign(const size_t &count, const T &value) {
  resize(count);
  std::fill(begin(), end(), value);
}
#if 0
template <typename T>
template <typename InputIt, typename>
void Vector<T>::assign(InputIt first, InputIt last) {
  size_type distance = static_cast<size_type>(std::distance(first, last));
  reserve(distance);
  for (auto it = first; it != last; ++it) {
    push_back(*it);
  }
}
#endif
template<typename T>
detail::VectorIterator<T> Vector<T>::insert(const_iterator pos, const T& value)
{
    auto distance = std::distance(this->cbegin(), pos);
    if (m_capacity == m_actual_size) {
        const size_type new_cap = m_capacity * 2;
        resize(new_cap);
    }
    //std::rotate(begin() + distance, end(), end() + 1);
    for (ssize_t i = static_cast<ssize_t>(m_actual_size) - 1; i >= distance; i--) {
        m_data[i + 1] = m_data[i];
    }
    m_data[distance] = value;
    m_actual_size++;
    return begin() + distance;
}
template<typename T>
template<typename ...Args>
void Vector<T>::emplace_back(Args&& ...args)
{
    if (m_actual_size == m_capacity) {
        m_capacity *= 2;
        reserve(m_capacity);
    }
    assert(m_data != nullptr);
    new (&m_data[m_actual_size]) T(std::forward<Args>(args) ...);
    m_actual_size++;
}
template<typename T>
bool Vector<T>::empty() const
{
    return m_actual_size == 0;
}
template<typename T>
void Vector<T>::shrink_to_fit()
{
    if (m_capacity > m_actual_size) {
        resize(m_actual_size);
    }
}
template<typename T>
void Vector<T>::pop_back()
{
    m_actual_size--;
    resize(m_actual_size);
}
template<typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos)
{
    if (pos == end()) {
        return end();
    }

    std::move(begin() + pos + 1, end(), begin() + pos);
    --m_actual_size;
    m_data[m_actual_size].~T();

    return begin() + pos;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last)
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
template<typename T>
template<typename InputIt>
void Vector<T>::assign(InputIt first, InputIt last)
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
