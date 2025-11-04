#include "circular_buffer.h"

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(size_type capacity)
    : buffer_(capacity), capacity_(capacity), head_(0U), tail_(0U), count_(0U)
{
    if (capacity_ == 0U) {
        throw std::domain_error("Capacity must be greater than zero");
    }
}

template <typename T>
void circular_buffer<T>::write(const T& item)
{
    if (is_full()) {
        throw std::domain_error("Buffer is full");
    }
    buffer_[tail_] = item;
    tail_ = (tail_ + 1U) % capacity_;
    count_ = count_ + 1U;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& item)
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
T circular_buffer<T>::read()
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
bool circular_buffer<T>::is_empty() const
{
    return (count_ == 0U);
}

template <typename T>
bool circular_buffer<T>::is_full() const
{
    return (count_ == capacity_);
}

template <typename T>
void circular_buffer<T>::clear()
{
    head_ = 0U;
    tail_ = 0U;
    count_ = 0U;
}

// Explicit instantiations for common types (optional, but may help some build systems)
// template class circular_buffer<std::int32_t>;
// template class circular_buffer<char>;
// template class circular_buffer<std::uint8_t>;

}  // namespace circular_buffer
