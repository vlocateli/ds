#pragma once
#ifndef TIMER_HPP
#define TIMER_HPP 1
#include <chrono>
#include <cassert>

using namespace std::chrono_literals;

template<class DT = std::chrono::milliseconds,
         class ClockT = std::chrono::steady_clock>
class Timer{
    using time_t = decltype(ClockT::now());

    time_t m_start = ClockT::now();
    time_t m_end   = {};

    public:
        void tick() {
            m_end = time_t{};
            m_start = ClockT::now();
        }

        void tock() {
            m_end = ClockT::now();
        }

        template<class duration_t = DT>
        auto duration() const {
           assert( m_end != time_t{} && "Timer must toc() before reading the time\n");

           return std::chrono::duration_cast<duration_t>(m_end - m_start);
        }
};
#endif // TIMER_HPP
