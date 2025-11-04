#include "circular_buffer.h"

namespace circular_buffer {

template <typename T>
CircularBuffer<T>::CircularBuffer(typename CircularBuffer<T>::size_type capacity)
    : buffer_(capacity), capacity_(capacity), head_(0U), tail_(0U), count_(0U)
{
    // No further initialization required
}

template <typename T>
void CircularBuffer<T>::write(const T& item)
{
    if (is_full()) {
        throw std::domain_error("Buffer is full");
    }
    buffer_[tail_] = item;
    tail_ = (tail_ + 1U) % capacity_;
    count_ = count_ + 1U;
}

template <typename T>
void CircularBuffer<T>::overwrite(const T& item)
{
    if (is_full()) {
        buffer_[head_] = item;
        head_ = (head_ + 1U) % capacity_;
        tail_ = (tail_ + 1U) % capacity_;
    } else {
        write(item);
    }
}

template <typename T>
T CircularBuffer<T>::read()
{
    if (is_empty()) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer_[head_];
    head_ = (head_ + 1U) % capacity_;
    count_ = count_ - 1U;
    return value;
}

template <typename T>
bool CircularBuffer<T>::is_empty() const
{
    return (count_ == 0U);
}

template <typename T>
bool CircularBuffer<T>::is_full() const
{
    return (count_ == capacity_);
}

template <typename T>
void CircularBuffer<T>::clear()
{
    head_ = 0U;
    tail_ = 0U;
    count_ = 0U;
}

// Explicit template instantiations for common types (add more as needed)

}  // namespace circular_buffer
