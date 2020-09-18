#include "../headers/DataBuffer.hpp"

using namespace mp;

DataQueue::DataQueue(DataQueue::Size capacity, Filter filter__, double default_value)
    : capacity{capacity},
      filter{ filter__ },
      default_value{default_value}
{
    while (_data.size() < capacity)
        _data.push_back(default_value);
}

DataQueue::~DataQueue() {}

void DataQueue::Update(double next)
{
    // Remove the oldest data element
    _data.pop_front();

    // Filter and add the next element
    next = filter(next);
    _data.push_back(next);
}

void DataQueue::SetSize(DataQueue::Size new_size)
{
    DataQueue::Size n = _data.size();

    capacity = new_size;

    while (n < capacity)
        _data.push_back(default_value);

    while (n > capacity)
        _data.pop_front();
}

DataQueue::Size DataQueue::GetSize() const { return capacity; }