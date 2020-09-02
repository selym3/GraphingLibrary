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