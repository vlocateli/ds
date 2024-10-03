#pragma once
#include "node.hpp"
#include <iostream>
#include <assert.h>
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
            {
                deallocate_list();
                auto tmp = list.m_list;
                while(tmp != nullptr) {
                    SLLNode<T>* p = tmp;
                    push_back(p->value());
                    tmp = tmp->next();
                }
                auto tmp_tail = list.m_tail;
                m_tail = tmp_tail;
                m_size = list.m_size;
            }
            LinkedList(const LinkedList&& list)
            {
            }
            LinkedList& operator= (const LinkedList& list)
            {
            }
            LinkedList& operator= (const LinkedList&& list)
            {
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
                (void) val;
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
