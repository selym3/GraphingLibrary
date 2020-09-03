#ifndef __FILTER_HPP__

/*
Filter design credits: Sam Belliveau
*/

#include "Timer.hpp"

#include <deque>
#include <cstdint>

namespace mp
{
    struct Filter
    {
        virtual double operator()(double next) = 0;
        // virtual ~Filter();
    };

    struct LowPassFilter : public Filter
    {
        LowPassFilter(double rc);
        virtual double operator()(double next) override;
    private:
        double rc; // const
        double last_value;
        Timer timer;
    };

    struct MovingAverage : public Filter
    {
        MovingAverage(std::size_t count);
        virtual double operator()(double next) override; 
    private:
        std::deque<double> values;
        double total;

        std::size_t count;
    };

}

#endif