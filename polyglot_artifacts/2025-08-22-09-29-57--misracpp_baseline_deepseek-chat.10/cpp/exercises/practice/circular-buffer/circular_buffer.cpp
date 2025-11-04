#include "circular_buffer.h"
#include <stdexcept>
#include <string>

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(size_t capacity) 
    : buffer(capacity), capacity(capacity), size_(0), head(0), tail(0) {
}

template <typename T>
T circular_buffer<T>::read() {
    if (size_ == 0) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer[head];
    head = (head + 1) % capacity;
    --size_;
    return value;
}

template <typename T>
void circular_buffer<T>::write(const T& data) {
    if (size_ == capacity) {
        throw std::domain_error("Buffer is full");
    }
    buffer[tail] = data;
    tail = (tail + 1) % capacity;
    ++size_;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& data) {
    if (size_ == capacity) {
        // Write to the current tail position, which is where the next element would be written
        // But when full, tail and head are at the same position, which contains the oldest element
        buffer[tail] = data;
        // Move tail forward
        tail = (tail + 1) % capacity;
        // Move head forward to point to the new oldest element
        head = tail;
    } else {
        write(data);
    }
}

template <typename T>
void circular_buffer<T>::clear() {
    size_ = 0;
    head = 0;
    tail = 0;
}

// Explicit instantiations for types used by tests
template class circular_buffer<int>;
template class circular_buffer<std::string>;

}  // namespace circular_buffer
