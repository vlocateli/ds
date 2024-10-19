#ifndef SLLIST_HPP
#define SLLIST_HPP 1
#pragma once
#include <iostream>
#include <assert.h>
#include "node.hpp"
#include "sllistiterator.hpp"
#define CHECK_BOUNDARIES 1 
#define DEBUG 1
#ifdef DEBUG
#include <iostream>
#ifndef CHECK_BOUNDARIES
#define CHECK_BOUNDARIES 1 
#endif // CHECK_BOUNDARIES
#define DEBUG_PRINT(x)\
    std::cerr << #x << ": " << x << '\n';
#endif // DEBUG
namespace ds{
    template<typename T>
    class LinkedList{
        public:
            LinkedList() noexcept:
                m_list{nullptr},
                m_tail{nullptr},
                m_size{0}
            {
            
            }
            LinkedList(const T& val) noexcept
            {
                auto new_node = new SLLNode<T>(val);
                m_tail = new_node;
                m_list = new_node;
                m_size = 1;
            }
            LinkedList(const LinkedList& list)
                :
                    m_list{nullptr},
                    m_tail{nullptr},
                    m_size{0}
            {
                if (list.m_list == nullptr) {
                    return;
                }
                auto tmp = list.m_list;
                while(tmp != nullptr) {
                    push_back(tmp->value_ref());
                    tmp = tmp->next();
                }
            }
            LinkedList(LinkedList&& other) noexcept:
                m_list{other.m_list},
                m_tail{other.m_tail},
                m_size{other.m_size}

            {
                other.m_list = nullptr;
                other.m_tail = nullptr;
                other.m_size = 0;
                
            }
            LinkedList& operator= (const LinkedList& list)
            {
                if (this == &list) {
                    return *this;
                }
                clear();
                auto tmp = list.m_list;
                while (tmp != nullptr) {
                    push_back(list.value_ref());
                    tmp = tmp->next();
                }

                return *this;
            }
            LinkedList& operator= (LinkedList&& other)
            {
                if (&other == this) {
                    return *this;
                }
                deallocate_list();
                m_list = other.list;
                m_size = other.size;
                m_tail = other.m_tail;
                other.m_list = nullptr;
                other.m_tail = nullptr;
                other.m_size = 0;
                return *this;
            }
            bool operator== (const LinkedList& other)
            {
                if (other.m_size != this->m_size) {
                    return false;
                }
                auto tmp = this->m_list;
                while (tmp != nullptr) {
                    if (tmp->value() != other->value()) {
                        return false;
                    }
                    tmp = tmp->next();
                    other = other->next();
                }
            }
            bool is_empty() const
            {
                return m_size == 0;
            }
            void clear()
            {
                deallocate_list();
                m_list = nullptr;
                m_tail = nullptr;
                m_size = 0;
            }
            T& at(const size_t index) const
            {
                auto tmp = m_list;
#ifdef CHECK_BOUNDARIES
                if (index >= m_size) {
                    DEBUG_PRINT(index);
                    throw std::out_of_range
                          ("ERROR: Index out of range in at()\n");
                }
#endif // CHECK_BOUNDARIES
                if (index == m_size - 1) {
                    return m_tail->value_ref();
                }
                for (size_t i = 0; i < index; i++) {
                    tmp = tmp->next();
                }
                return tmp->value_ref();

            }
            ~LinkedList() noexcept
            {
                deallocate_list();
            }
            size_t size() const
            {
                return m_size;
            }
            void push_back(const T& val)
            {
                auto new_node = new SLLNode<T>(val);
                if (m_size == 0) {
                    m_list = new_node;
                    m_tail = new_node;
                } else{
                    m_tail->set_next(new_node);
                    m_tail = new_node;
                }
                m_size++;
                return;
            }
            void push_back(const T&& val)
            {
                auto new_node = new SLLNode<T>(std::move(val));
                if (m_size == 0) {
                    m_list = new_node;
                    m_tail = new_node;
                } else{
                    m_tail->set_next(new_node);
                    m_tail = new_node;
                }
                m_size++;
                return;
            }
            T pop_back()
            {
                auto head = m_list;
                ds::SLLNode<T>* previous = nullptr;
                T pop_value {};
                if (m_size == 1) {
                    pop_value = head->value();
                    deallocate_list();
                    return pop_value;
                }
                while (head != m_tail) {
                    previous = head;
                    head = head->next();
                }
                previous->set_next(nullptr);
                auto tmp = head;
                pop_value = head->value();
                delete tmp;
                m_tail = previous;
                m_size--;
                return pop_value;
            }
            const T* search(const T& val)
            {
                auto tmp = m_list;
                while (tmp != nullptr) {
                    if (tmp->value() == val) {
                        return &(tmp->value_ref());
                    }
                    tmp = tmp->next();
                }
                return nullptr;
            }
            T minimum() const
            {
                auto tmp = m_list;
                T minimum = tmp->value(); 
                while (tmp != nullptr) {
                   if (tmp->value() > minimum) {
                       minimum = tmp->value();
                   }
                   tmp = tmp->next();
                }
                return minimum;
            }
            T maximum() const 
            {
                auto tmp = m_list;
                T maximum = tmp->value(); 
                while (tmp != nullptr) {
                    if (tmp->value() < maximum) {
                        maximum = tmp->value();
                    }
                    tmp = tmp->next();
                }
                return maximum;
            }
            T find_middle() const
            {
                size_t mid_index = m_size;
                mid_index  = mid_index % 2 == 0 ? mid_index/2:(mid_index/2) + 1; 
                T middle_value = at(mid_index);
                return middle_value; 
                
            }
            size_t find(const T& value) const
            {
                if (m_tail->value() == value) {
                    return m_size - 1;
                }
                size_t i;
                for (i = 0; i < m_size - 1; i++) {
                   if (this->at(i) == value) {
                       break;
                   }
                }
                return i;
            }
            T pop_front()
            {
                auto head = m_list;
                ds::SLLNode<T>* previous = nullptr;
                T pop_value {};
                if (m_size == 1) {
                    pop_value = m_list->value();
                    deallocate_list();
                    return pop_value;
                }
                previous = head;
                head = head->next();
                m_list = head;
                pop_value = previous->value();
                delete previous;
                m_size--;
                return pop_value;
            }
            bool remove(const T& value)
            {
                size_t index = this->find(value);
                if (index == 0) {
                    pop_front();
                    m_size--;
                    return true;
                }
                else if (index == m_size - 1) {
                    pop_back();
                    m_size--;
                    return true;
                }
                ds::SLLNode<T> *previous = nullptr;
                auto head = m_list->next();
                for (size_t i = 1; i < index; i++) {
                    previous = head;
                    head = head->next();
                }
                previous->set_next(head->next());
                auto node_to_delete = head;
                delete node_to_delete;
                m_size--;
                return true;
            }
            friend std::ostream& operator<< (std::ostream& stream,
                                      const ds::LinkedList<T> &list)
            {
                auto tmp = list.m_list;

                while (tmp != nullptr) {
                    stream << tmp->value() << " ";
                    tmp = tmp->next();
                }

                return stream;
            }
            ds::detail::Iterator<T> begin()
            {
            return ds::detail::Iterator<T>(m_list);
            }
            ds::detail::Iterator<T> end()
            {
                return ds::detail::Iterator<T>(nullptr);
            }
        private:
            void deallocate_list() noexcept
            {
                auto head = m_list;
                while (head != nullptr)
                {
                    auto p = head;
                    head = head->next();
                    delete p;
                }
                m_list = nullptr;
                m_tail = nullptr;
                m_size = 0;
                
            }
            SLLNode<T>* m_list;
            SLLNode<T>* m_tail;
            size_t   m_size;

};
} // namespace ds
#endif // SLLIST_HPP
