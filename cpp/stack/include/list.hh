#ifndef LIST_HH
#define LIST_HH 1
#include <iostream>
#define DEBUG 1
#ifdef DEBUG
#include <utility>
template <typename... Args> constexpr void dbg_print(Args &&...args) noexcept {
  ((std::cerr << std::forward<Args>(args) << ' '), ...);
}
#include <cassert>
#endif // DEBUG
template <typename T> 
struct List {
  struct Node {
    using Data = T;
    Data m_data;
    Node *m_next;
    Node(const Data &p) : m_data{p}, m_next{nullptr} {}
  };
  Node *m_list;
  size_t m_size;
  using Data = T;

  List() : m_list{nullptr}, m_size{0} {}
  List(const Data& d){
    try{
        m_list = new Node(d);
        m_list->m_next = nullptr;
        m_list->m_data = d;
        m_size++;
    }catch(std::bad_alloc()){
        std::cerr << "[ERROR]: Could not allocate memory\n";
        std::exit(EXIT_FAILURE);
    }
  }
  ~List(){
#if 0
    auto *current{m_list};
    while(current->m_next != nullptr){
        auto *p = current->m_list;
        delete p;
    }
    m_list  = nullptr;
    m_size  = 0;
#endif
  }
  bool insert_end(const Data &d) {
#if 0
    if (m_list == nullptr) {
      m_list = new Node(d);
      m_list->m_next = nullptr;
      m_list->m_data = d;
      m_size++;
      return true;
    }
#endif
    auto *new_node{new Node(d)};
    auto current{m_list};
    while (current != nullptr) {
      current = m_list->m_next;
    }
    current = new_node;
    current->m_next = nullptr;
    m_list = current;
    m_size++;
    delete new_node;
    return true;
  }
  bool insert_at_n(const Data &d, const size_t &position) {
    Node *p = nullptr; // current
    Node *q = nullptr; // next
    size_t i = 0;
    p = this;
    while (i != position - 1) {
      p = p->m_next;
      q = p->m_next;
      i++;
    }
    Node *new_node = new Node(d);
    p->m_next = new_node;
    new_node->m_next = q;
    return true;
  }
#if 0
    ~List(){
        List<Data> *current = this;
        while(current->m_list != nullptr){
            auto *aux = &current;
            delete aux;
            current->m_list = current->m_list->m_next;
        }
    }
#endif
  friend std::ostream &operator<<(std::ostream &stream, const List<T> &list) {
    auto current {list.m_list};
    if (current == nullptr) {
      std::cerr << "[ERROR]: nullptr dereferencing\n";
      return stream;
    }
    while (current != nullptr) {
      stream << current->m_data << ' ';
      current = current->m_next;
    }

    return stream;
  }
};

#endif // LIST_HH
