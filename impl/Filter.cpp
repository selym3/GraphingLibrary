#include "../headers/Filter.hpp"

using namespace mp;

/*
Filter design credits: Sam Belliveau
*/

Filter::Filter() {}
Filter::~Filter() {}

NoFilter::NoFilter() {}
NoFilter::~NoFilter() {}
double NoFilter::operator()(double next) { return next; }
NoFilter::PointerType NoFilter::clone() const
{
    return NoFilter::PointerType(new NoFilter());
}


LowPassFilter::LowPassFilter(double rc): rc{rc} {}
double LowPassFilter::operator()(double next)
{
    double dt = timer.Poll();
    double a = dt / (rc+dt);
    return last_value += a * (next - last_value);
}
LowPassFilter::~LowPassFilter() {}
LowPassFilter::PointerType LowPassFilter::clone() const
{
    return LowPassFilter::PointerType(new LowPassFilter(this->rc));
}

MovingAverage::MovingAverage(std::size_t count): count{count}, total{0.0}
{
    while (values.size() < count)
        values.push_back(0.0);
}
MovingAverage::~MovingAverage() {}
double MovingAverage::operator()(double next) 
{
    // remove the first element and its consideration
    // from the running total
    total -= values.front();
    values.pop_front();

    // add the newest element to and add it to the running sum
    total += next;
    values.push_back(next);

    return total / count;
}
MovingAverage::PointerType MovingAverage::clone() const
{
    MovingAverage* m_ptr = new MovingAverage(this->count);
    m_ptr->total = total;

    for (const double& value : values)
    {
        m_ptr->values.pop_front();
        m_ptr->values.push_back(value);
    }

    return MovingAverage::PointerType(m_ptr);
}