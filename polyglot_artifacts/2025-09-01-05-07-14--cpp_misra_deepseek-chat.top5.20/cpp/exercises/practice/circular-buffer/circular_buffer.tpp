#if !defined(CIRCULAR_BUFFER_TPP)
#define CIRCULAR_BUFFER_TPP

#include "circular_buffer.h"
#include <stdexcept>

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(std::uint32_t capacity) 
    : buffer_(capacity), head_(0U), tail_(0U), count_(0U), capacity_(capacity) {
}

template <typename T>
T circular_buffer<T>::read() {
    if (empty()) { 
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer_[head_];
    head_ = ((head_ + 1U) % capacity_);
    count_--;
    return value;
}

template <typename T>
void circular_buffer<T>::write(const T& data) {
    if (full()) { 
        throw std::domain_error("Buffer is full");
    }
    buffer_[tail_] = data;
    tail_ = ((tail_ + 1U) % capacity_);
    count_++;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& data) {
    if (full()) { 
        // Overwrite the oldest element (head)
        read();
    } else {
        // Do nothing
    }
    write(data);
}

template <typename T>
void circular_buffer<T>::clear() {
    head_ = 0U;
    tail_ = 0U;
    count_ = 0U;
}

template <typename T>
std::uint32_t circular_buffer<T>::size() const {
    return count_;
}

template <typename T>
std::uint32_t circular_buffer<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool circular_buffer<T>::empty() const {
    return (count_ == 0U);
}

template <typename T>
bool circular_buffer<T>::full() const {
    return (count_ == capacity_);
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_TPP
