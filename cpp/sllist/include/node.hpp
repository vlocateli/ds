#pragma once
namespace ds{
    template<typename T>
    class SLLNode{
        public:
            SLLNode()
            {
            }
            SLLNode(const T& value):
                m_value{value},
                m_next{nullptr}
            {
            }
            T value() const
            {
                return m_value;
            }
            void value(const T& value)
            {
                m_value = value;
            }
            SLLNode* next() const
            {
                return m_next;
            }
            void set_next(SLLNode* next)
            {
                m_next = next;
            }
        private:
            T m_value;
            SLLNode* m_next;
    };
}
