#pragma once
namespace ds{
    template<typename T>
    class Node{
        public:
            Node()
            {
            }
            Node(const T& value):
                m_value{value},
                m_next{nullptr}
            {
            }
            T value() const
            {
                return m_value;
            }
            T& value_ref()
            {
                return m_value;
            }
            void value(const T& value)
            {
                m_value = value;
            }
            Node* next() const
            {
                return m_next;
            }
            void set_next(Node* next)
            {
                m_next = next;
            }
        private:
            T m_value;
            Node* m_next;
    };
}
