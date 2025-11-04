#include "circular_buffer.h"
#include <stdexcept>
#include <cstdint>
#include <string>

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(std::uint32_t size) 
    : buffer(size), head(0U), tail(0U), count(0U), capacity_(size) {
}

template <typename T>
T circular_buffer<T>::read() {
    if (empty()) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer[head];
    head = ((head + 1U) % capacity_);
    count--;
    return value;
}

template <typename T>
void circular_buffer<T>::write(const T& data) {
    if (full()) {
        throw std::domain_error("Buffer is full");
    }
    buffer[tail] = data;
    tail = ((tail + 1U) % capacity_);
    count++;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& data) {
    if (full()) {
        // When full, the next write will overwrite the oldest element at head
        // Write to tail, then move both pointers forward
        buffer[tail] = data;
        tail = ((tail + 1U) % capacity_);
        head = tail; // Since the buffer is full, head should point to the new oldest element
    } else {
        write(data);
    }
}

template <typename T>
void circular_buffer<T>::clear() {
    head = 0U;
    tail = 0U;
    count = 0U;
}

// Explicit instantiation for types used in tests
#include <string>
template class circular_buffer<int>;
template class circular_buffer<std::string>;

}  // namespace circular_buffer
