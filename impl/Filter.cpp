#include "../headers/Filter.hpp"

using namespace mp;

/*
Filter design credits: Sam Belliveau
*/

LowPassFilter::LowPassFilter(double rc): rc{rc} {}
double LowPassFilter::operator()(double next)
{
    double dt = timer.Poll();
    double a = dt / (rc+dt);
    return last_value += a * (next - last_value);
}

MovingAverage::MovingAverage(std::size_t count): count{count}, total{0.0}
{
    while (values.size() < count)
        values.push_back(0.0);
}
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