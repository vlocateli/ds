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
template<typename T>
using iterator = ds::detail::Iterator<T>;
namespace ds{
    template<typename T>
    class LinkedList 
    {
        public:
            friend iterator<T>;
            LinkedList() noexcept:
                list_{nullptr},
                tail_{nullptr},
                size_{0}
            {
            
            }
            LinkedList(const T& val) noexcept
            {
                auto new_node = new SLLNode<T>(val);
                tail_ = new_node;
                list_ = new_node;
                size_ = 1;
            }
            LinkedList(const LinkedList& list)
                :
                    list_{nullptr},
                    tail_{nullptr},
                    size_{0}
            {
                if (list.list_ == nullptr) {
                    return;
                }
                auto tmp = list.list_;
                while(tmp != nullptr) {
                    push_back(tmp->value_ref());
                    tmp = tmp->next();
                }
            }
            LinkedList(LinkedList&& other) noexcept:
                list_{other.list_},
                tail_{other.tail_},
                size_{other.size_}

            {
                other.list_ = nullptr;
                other.tail_ = nullptr;
                other.size_ = 0;
                
            }
            LinkedList& operator= (const LinkedList& list)
            {
                if (this == &list) {
                    return *this;
                }
                clear();
                auto tmp = list.list_;
                while (tmp != nullptr) {
                    push_back(tmp->value_ref());
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
                list_ = other.list_;
                size_ = other.size_;
                tail_ = other.tail_;
                other.list_ = nullptr;
                other.tail_ = nullptr;
                other.size_ = 0;
                return *this;
            }
            bool operator== (const LinkedList& other)
            {
                if (other.size_ != this->size_) {
                    return false;
                }
                auto tmp = this->list_;
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
                return size_ == 0;
            }
            void clear()
            {
                deallocate_list();
                list_ = nullptr;
                tail_ = nullptr;
                size_ = 0;
            }
            T& at(const size_t index) const
            {
                auto tmp = list_;
#ifdef CHECK_BOUNDARIES
                if (index >= size_) {
                    DEBUG_PRINT(index);
                    throw std::out_of_range
                          ("ERROR: Index out of range in at()\n");
                }
#endif // CHECK_BOUNDARIES
                if (index == size_ - 1) {
                    return tail_->value_ref();
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
                return size_;
            }
            void push_back(const T& val)
            {
                auto new_node = new SLLNode<T>(val);
                if (size_ == 0) {
                    list_ = new_node;
                    tail_ = new_node;
                } else{
                    tail_->set_next(new_node);
                    tail_ = new_node;
                }
                size_++;
                return;
            }
            void push_back(const T&& val)
            {
                auto new_node = new SLLNode<T>(std::move(val));
                if (size_ == 0) {
                    list_ = new_node;
                    tail_ = new_node;
                } else{
                    tail_->set_next(new_node);
                    tail_ = new_node;
                }
                size_++;
                return;
            }
            T pop_back()
            {
                auto head = list_;
                ds::SLLNode<T>* previous = nullptr;
                T pop_value {};
                if (size_ == 1) {
                    pop_value = head->value();
                    deallocate_list();
                    return pop_value;
                }
                while (head != tail_) {
                    previous = head;
                    head = head->next();
                }
                previous->set_next(nullptr);
                auto tmp = head;
                pop_value = head->value();
                delete tmp;
                tail_ = previous;
                size_--;
                return pop_value;
            }
            const T* search(const T& val)
            {
                auto tmp = list_;
                while (tmp != nullptr) {
                    if (tmp->value() == val) {
                        return &(tmp->value_ref());
                    }
                    tmp = tmp->next();
                }
                return nullptr;
            }
            T maximum() const
            {
                auto tmp = list_;
                T maximum = tmp->value(); 
                while (tmp != nullptr) {
                   if (tmp->value() > maximum) {
                       maximum = tmp->value();
                   }
                   tmp = tmp->next();
                }
                return maximum;
            }
            T minimum() const 
            {
                auto tmp = list_;
                T minimum = tmp->value(); 
                while (tmp != nullptr) {
                    if (tmp->value() < minimum) {
                        minimum = tmp->value();
                    }
                    tmp = tmp->next();
                }
                return minimum;
            }
            T find_middle() const
            {
                size_t mid_index = size_;
                mid_index  = mid_index % 2 == 0 ? mid_index/2:(mid_index/2) + 1; 
                T middle_value = at(mid_index);
                return middle_value; 
                
            }
            size_t find(const T& value) const
            {
                if (tail_->value() == value) {
                    return size_ - 1;
                }
                size_t i;
                for (i = 0; i < size_ - 1; i++) {
                   if (this->at(i) == value) {
                       break;
                   }
                }
                return i;
            }
            T pop_front()
            {
                auto head = list_;
                ds::SLLNode<T>* previous = nullptr;
                T pop_value {};
                if (size_ == 1) {
                    pop_value = list_->value();
                    deallocate_list();
                    return pop_value;
                }
                previous = head;
                head = head->next();
                list_ = head;
                pop_value = previous->value();
                delete previous;
                size_--;
                return pop_value;
            }
            T push_front(const T& val)
            {
                ds::SLLNode<T>* new_node{nullptr};
                new_node = new ds::SLLNode<T>(val);
                if (is_empty()) {
                    list_ = new_node;
                    tail_ = new_node;
                    size_++;
                    return val;
                }
                auto head = list_;
                new_node->set_next(head);
                list_ = new_node;
                size_++;
                return val;
            }
            bool remove(const T& value)
            {
                size_t index = this->find(value);
                if (index == 0) {
                    pop_front();
                    size_--;
                    return true;
                }
                else if (index == size_ - 1) {
                    pop_back();
                    size_--;
                    return true;
                }
                ds::SLLNode<T> *previous = nullptr;
                auto head = list_->next();
                for (size_t i = 1; i < index; i++) {
                    previous = head;
                    head = head->next();
                }
                previous->set_next(head->next());
                auto node_to_delete = head;
                delete node_to_delete;
                size_--;
                return true;
            }
            void reverse()
            {
                ds::LinkedList<T> head_q;
                ds::LinkedList<T> head_p = *this;
                while (!head_p.is_empty()) {
                   T val = head_p.pop_back();
                   head_q.push_back(val);
                }
                *this = head_q;
            }
            friend std::ostream& operator<< (std::ostream& stream,
                                      const ds::LinkedList<T> &list)
            {
                auto tmp = list.list_;

                while (tmp != nullptr) {
                    stream << tmp->value() << " ";
                    tmp = tmp->next();
                }

                return stream;
            }
            ds::detail::Iterator<T> begin()
            {
            return ds::detail::Iterator<T>(list_);
            }
            ds::detail::Iterator<T> end()
            {
                return ds::detail::Iterator<T>(nullptr);
            }
            iterator<T>  insert_after(iterator<T> pos, const T& value)

            {
                assert(pos.ptr() != nullptr && "cant insert after end iterator");
                auto new_node = new SLLNode<T>(value);
                new_node->set_next(pos.ptr()->next());
                pos.ptr()->set_next(new_node);
                return iterator<T>(new_node);

            }
        private:
            void deallocate_list() noexcept
            {
                auto head = list_;
                while (head != nullptr)
                {
                    auto p = head;
                    head = head->next();
                    delete p;
                }
                list_ = nullptr;
                tail_ = nullptr;
                size_ = 0;
                
            }
            SLLNode<T>* list_;
            SLLNode<T>* tail_;
            size_t   size_;

};
} // namespace ds
#endif // SLLIST_HPP
