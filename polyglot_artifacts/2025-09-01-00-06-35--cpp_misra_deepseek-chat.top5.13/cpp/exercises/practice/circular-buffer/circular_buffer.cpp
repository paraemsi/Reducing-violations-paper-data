#include "circular_buffer.h"
#include <stdexcept>
#include <string>

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(std::uint32_t size) 
    : buffer(size), head(0U), tail(0U), count(0U), capacity_(size) {
}

template <typename T>
T circular_buffer<T>::read() {
    if (count == 0U) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer[head];
    head = (head + 1U) % capacity_;
    --count;
    return value;
}

template <typename T>
void circular_buffer<T>::write(const T& data) {
    if (count == capacity_) {
        throw std::domain_error("Buffer is full");
    }
    buffer[tail] = data;
    tail = (tail + 1U) % capacity_;
    ++count;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& data) {
    if (count < capacity_) {
        write(data);
    } else {
        // Buffer is full, overwrite the oldest element at head
        buffer[head] = data;
        // Move head to the next oldest element
        head = (head + 1U) % capacity_;
        // Tail should also move to maintain full state
        tail = head;
        // count remains at capacity_
    }
}

template <typename T>
void circular_buffer<T>::clear() {
    head = 0U;
    tail = 0U;
    count = 0U;
}

// Explicit template instantiation for common types
template class circular_buffer<int>;
template class circular_buffer<std::string>;
// Add other types as needed

}  // namespace circular_buffer
