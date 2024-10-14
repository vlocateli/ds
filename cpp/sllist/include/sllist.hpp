#pragma once
#include "node.hpp"
#include <iostream>
#include <assert.h>
#include <limits>
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
                auto tmp = m_list;
                ds::SLLNode<T> *before = nullptr;
                while (tmp->next() != nullptr) {
                    before = tmp;
                    tmp = tmp->next();
                }
               
                std::cout << tmp->value() << '\n';
                return (0);
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
            T minimum(){
                auto tmp = m_list;
                T minimum = std::numeric_limits<T>::min(); 
                while (tmp != nullptr) {
                   if (tmp->value() > minimum) {
                       minimum = tmp->value();
                   }
                   tmp = tmp->next();
                }
                return minimum;
            }
            T maximum() 
            {
                auto tmp = m_list;
                T maximum = std::numeric_limits<T>::max();
                while (tmp != nullptr) {
                    if (tmp->value() < maximum) {
                        maximum = tmp->value();
                    }
                    tmp = tmp->next();
                }
                return maximum;
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
                
            }
            SLLNode<T>* m_list;
            SLLNode<T>* m_tail;
            size_t   m_size;
    };
}
