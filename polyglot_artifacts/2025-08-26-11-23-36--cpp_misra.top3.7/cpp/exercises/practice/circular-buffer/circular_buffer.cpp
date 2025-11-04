#include "circular_buffer.h"

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(size_type capacity)
    : buffer_(capacity), head_(0U), tail_(0U), count_(0U), max_size_(capacity)
{
    if (capacity == 0U) {
        throw std::invalid_argument("Capacity must be greater than zero");
    }
}

template <typename T>
void circular_buffer<T>::write(const T& item)
{
    if (is_full()) {
        throw std::domain_error("Buffer is full");
    }
    buffer_[tail_] = item;
    tail_ = (tail_ + 1U) % max_size_;
    count_ = count_ + 1U;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& item)
{
    if (is_full()) {
        buffer_[head_] = item;
        head_ = (head_ + 1U) % max_size_;
        tail_ = (tail_ + 1U) % max_size_;
    } else {
        write(item);
    }
}

template <typename T>
T circular_buffer<T>::read()
{
    if (is_empty()) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer_[head_];
    head_ = (head_ + 1U) % max_size_;
    count_ = count_ - 1U;
    return value;
}

template <typename T>
void circular_buffer<T>::clear()
{
    head_ = 0U;
    tail_ = 0U;
    count_ = 0U;
}

template <typename T>
bool circular_buffer<T>::is_empty() const
{
    return (count_ == 0U);
}

template <typename T>
bool circular_buffer<T>::is_full() const
{
    return (count_ == max_size_);
}

template <typename T>
typename circular_buffer<T>::size_type circular_buffer<T>::capacity() const
{
    return max_size_;
}

template <typename T>
typename circular_buffer<T>::size_type circular_buffer<T>::size() const
{
    return count_;
}

}  // namespace circular_buffer
