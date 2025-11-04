#include "circular_buffer.h"
#include <cstdint>
#include <vector>
#include <stdexcept>

namespace circular_buffer {

template<typename T>
circular_buffer<T>::circular_buffer(size_type capacity)
    : buffer_(capacity), head_(0U), tail_(0U), size_(0U), capacity_(capacity) {
}

template<typename T>
void circular_buffer<T>::write(value_type value) {
    if (full()) {
        throw std::runtime_error("Buffer is full");
    }
    buffer_[tail_] = value;
    tail_ = (tail_ + 1U) % capacity_;
    size_ = size_ + 1U;
}

template<typename T>
typename circular_buffer<T>::value_type circular_buffer<T>::read() {
    if (empty()) {
        throw std::runtime_error("Buffer is empty");
    }
    value_type value = buffer_[head_];
    head_ = (head_ + 1U) % capacity_;
    size_ = size_ - 1U;
    return value;
}

template<typename T>
void circular_buffer<T>::overwrite(value_type value) {
    buffer_[tail_] = value;
    tail_ = (tail_ + 1U) % capacity_;
    if (full()) {
        head_ = (head_ + 1U) % capacity_;
    } else {
        size_ = size_ + 1U;
    }
}

template<typename T>
void circular_buffer<T>::clear() {
    head_ = 0U;
    tail_ = 0U;
    size_ = 0U;
}

template<typename T>
bool circular_buffer<T>::empty() const {
    return (size_ == 0U);
}

template<typename T>
bool circular_buffer<T>::full() const {
    return (size_ == capacity_);
}

}  // namespace circular_buffer
