#ifndef __FILTER_HPP__

/*
Filter design credits: Sam Belliveau
*/

#include "Timer.hpp"

namespace mp
{
    struct Filter
    {
        virtual double operator()(double next) = 0;
    };

    struct LowPassFilter : public Filter
    {
        LowPassFilter(double rc);
        virtual double operator()(double next) override;
    private:
        double rc;
        double last_value;
        Timer timer;
    };

}

#endif