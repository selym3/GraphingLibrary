#include "../headers/DataBuffer.hpp"

using namespace mp;

DataQueue::DataQueue(DataQueue::Size capacity, Filter *raw_filter_ptr, double default_value)
    : capacity{capacity},
      filter{raw_filter_ptr ? raw_filter_ptr : new NoFilter()},
      default_value{default_value}
{
    while (_data.size() < capacity)
        _data.push_back(default_value);
}

DataQueue::~DataQueue() {}

DataQueue::DataQueue(const DataQueue& rhs)
    : capacity { rhs.capacity },
    // at this point i dont think rhs.filter can be null
      filter { (*rhs.filter).clone() },
      default_value { rhs.default_value },
    // it should be accurate if i just copied over the data
      _data { rhs._data }
{
}

DataQueue& DataQueue::operator=(const DataQueue& rhs)
{
    capacity = rhs.capacity;
    filter = (*rhs.filter).clone();
    default_value = rhs.default_value;

    SetSize(capacity);

    for (const double& value : rhs._data)
    {
        _data.pop_front();
        _data.push_back(value);
    }

    return * this;
}

void DataQueue::Update(double next)
{
    // Remove the oldest data element
    _data.pop_front();

    // Filter and add the next element
    next = (*filter)(next);
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