#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>

namespace mp
{

    /*
    I want to do the template base / derived model for the timer class
    but i dont remember how to do that
    */

    class Timer
    {
        using Clock = std::chrono::system_clock;
        Clock::time_point last;

    public:
        Timer(): last{Clock::now()} {}
        ~Timer() {}

        double Poll()
        {
            Clock::time_point now = Clock::now();
            std::chrono::duration<double> diff = now - last;
            last = now;
            return diff.count();
        }
    };

} // namespace mp

#endif