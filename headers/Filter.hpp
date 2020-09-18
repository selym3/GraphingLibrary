#ifndef __FILTER_HPP__

#include "Timer.hpp"

// deque not queue because queue doesnt have iterator (weird)
#include <deque>
#include <cstdint>

#include <functional>

namespace mp
{

    using Filter = std::function<double(double)>;

    Filter operator+(const Filter& a, const Filter& b)
    {
        return [a, b](double next) { return b(a(next)); }
    }

    struct NoFilter 
    {
        NoFilter();
        ~NoFilter();

        double operator()(double next);
    };

    struct LowPassFilter
    {
        LowPassFilter(double rc);
        ~LowPassFilter();

        double operator()(double next);

    private:
        double rc;
        double last_value;
        Timer timer;
    };

    struct MovingAverage
    {
        MovingAverage(std::size_t count);
        ~MovingAverage();

        double operator()(double next); 

    private:
        std::deque<double> values;
        double total;

        std::size_t count;
    };

    struct Value
    {
        double value, time;

        Value(double v, double t) : value { v * t } , time { t }
        {
        }

    };

    struct TimedMovingAverage
    {
        using Value = Value;

        TimedMovingAverage(double time);
        ~TimedMovingAverage();

        double operator()(double next);
    private:
        void Remove();
        void Add(double next);

        // timer
        mp::Timer timer;
        
        // running totals
        double total;
        double total_time;
        
        // max timeout
        double max_time;

        // data buffer
        std::deque<Value> data;

    };

}

#endif