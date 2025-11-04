#include "circular_buffer.h"
#include <stdexcept>

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(index_t size) 
    : buffer(size), head(0U), tail(0U), count(0U), capacity(size) {
}

template <typename T>
T circular_buffer<T>::read() {
    if (count == 0U) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer[head];
    head = (head + 1U) % capacity;
    --count;
    return value;
}

template <typename T>
void circular_buffer<T>::write(const T& data) {
    if (count == capacity) {
        throw std::domain_error("Buffer is full");
    }
    buffer[tail] = data;
    tail = (tail + 1U) % capacity;
    ++count;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& data) {
    if (count < capacity) {
        write(data);
    } else {
        // Overwrite the oldest element which is at head
        buffer[head] = data;
        head = (head + 1U) % capacity;
        tail = (tail + 1U) % capacity;
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

}  // namespace circular_buffer
