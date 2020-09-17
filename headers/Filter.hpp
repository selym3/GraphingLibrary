#ifndef __FILTER_HPP__

/*
Filter design credits: Sam Belliveau
*/

#include "Timer.hpp"

// deque not queue because queue doesnt have iterator (weird)
#include <deque>
#include <cstdint>

#include <memory>

namespace mp
{
    template <typename Base, typename Pointer = std::unique_ptr<Base>>
    struct Cloneable
    {
        typedef Base BaseType;
        typedef Pointer PointerType;

        virtual Pointer clone() const = 0;
    };

    struct Filter : Cloneable<Filter>
    {
        virtual double operator()(double next) = 0;
        
        // Filter(const Filter&) = default;
        // Filter& operator=(const Filter&) = default;

        Filter();
        virtual ~Filter();

        // virtual PointerType clone() = 0;

    };

    struct NoFilter final : public Filter
    {
        NoFilter();
        ~NoFilter();

        double operator()(double next) override;
        PointerType clone() const override;

    };

    struct LowPassFilter final : public Filter
    {
        LowPassFilter(double rc);
        ~LowPassFilter();

        double operator()(double next) override;
        PointerType clone() const override;

    private:
        double rc; // const
        double last_value;
        Timer timer;
    };

    struct MovingAverage final : public Filter
    {
        MovingAverage(std::size_t count);
        ~MovingAverage();

        double operator()(double next) override; 
        PointerType clone() const override;

    private:
        std::deque<double> values;
        double total;

        std::size_t count;
    };

}

#endif