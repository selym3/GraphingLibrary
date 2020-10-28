#include "../headers/Filter.hpp"

using namespace mp;

mp::Filter mp::operator+(const mp::Filter& a, const mp::Filter& b)
{
    return [a, b](double next) { return b(a(next)); };
}

NoFilter::NoFilter() {}
NoFilter::~NoFilter() {}
double NoFilter::operator()(double next) { return next; }

LowPassFilter::LowPassFilter(double rc): rc{rc} {}
double LowPassFilter::operator()(double next)
{
    double dt = timer.Poll();
    double a = dt / (rc+dt);
    return last_value += a * (next - last_value);
}
LowPassFilter::~LowPassFilter() {}

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

TimedMovingAverage::TimedMovingAverage(double time)
    : max_time { time },
      total { 0.0 }, total_time { 0.0 }
{

}

TimedMovingAverage::~TimedMovingAverage()
{
}

void TimedMovingAverage::Add(double next)
{
    TimedMovingAverage::Value v ( next, timer.Poll() );
    total += v.value;
    total_time += v.time;
    data.push_back(v);
}

void TimedMovingAverage::Remove()
{
    const TimedMovingAverage::Value v = data.front();
    data.pop_front();

    total -= v.value;
    total_time -= v.time;
}

double TimedMovingAverage::operator()(double next)
{
    while (max_time < total_time)
        Remove();

    Add(next);

    return (total_time > 0) * total / total_time; 

}