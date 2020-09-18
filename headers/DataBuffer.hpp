#ifndef __DATA_BUFFER_HPP__
#define __DATA_BUFFER_HPP__


// #include <queue>
#include <deque>
#include "Filter.hpp"
#include <memory>

namespace mp
{

class DataQueue
{
    /*
    Technically, only a raw a queue is needed,
    but i couldn't find any typedefs for iterators
    in std::queue and it looks like it's simply a 
    wrapper for a Sequence type that supports queue
    operations (e.g. deque)
    */

    using Size = std::size_t;
    using Queue = std::deque<double>; // std::queue<double>;

    Queue _data;
    Size capacity;

    double default_value;

    Filter filter;

public: 

    DataQueue(Size capacity, Filter filter, double default_value = 0.0);
    ~DataQueue();

    DataQueue(const DataQueue&) = default;
    DataQueue& operator=(const DataQueue&) = default;

    void Update(double next);

    void SetSize(Size new_size);
    Size GetSize() const;

    // TEMPORARY FUNCTIONS
    Queue::iterator begin() { return _data.begin(); }
    Queue::iterator end() { return _data.end(); }
    double front() { return _data.front(); }
    double rear() {  return _data.back(); }

};

};

#endif