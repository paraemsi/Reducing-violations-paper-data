#include "circular_buffer.h"
#include <stdexcept>

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(size_t capacity) 
    : buffer(capacity), capacity(capacity), size(0), head(0), tail(0) {
}

template <typename T>
T circular_buffer<T>::read() {
    if (size == 0) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer[head];
    head = (head + 1) % capacity;
    size--;
    return value;
}

template <typename T>
void circular_buffer<T>::write(const T& data) {
    if (size == capacity) {
        throw std::domain_error("Buffer is full");
    }
    buffer[tail] = data;
    tail = (tail + 1) % capacity;
    size++;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& data) {
    if (size < capacity) {
        write(data);
    } else {
        // Buffer is full, overwrite the oldest element which is at head
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        head = tail; // Since the buffer is full, head should now point to the new oldest element
        // Size remains at capacity
    }
}

template <typename T>
void circular_buffer<T>::clear() {
    size = 0;
    head = 0;
    tail = 0;
}

// Explicit template instantiation for int and std::string to satisfy the tests
template class circular_buffer<int>;
template class circular_buffer<std::string>;

}  // namespace circular_buffer
