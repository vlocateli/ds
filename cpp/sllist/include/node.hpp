#ifndef NODE_HPP
#define NODE_HPP 1
#pragma once
namespace ds{
    template<typename T>
    class SLLNode{
        public:
            SLLNode()
            {
            }
            SLLNode(const T& value):
                value_{value},
                next_{nullptr}
            {
            }
            T value() const
            {
                return value_;
            }
            T& value_ref()
            {
                return value_;
            }
            void value(const T& value)
            {
                value_ = value;
            }
            SLLNode* next() const
            {
                return next_;
            }
            void set_next(SLLNode* next)
            {
                next_ = next;
            }
        private:
            T value_;
            SLLNode* next_;
    };
}
#endif // NODE_HPP
