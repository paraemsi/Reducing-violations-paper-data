#include "circular_buffer.h"
#include <stdexcept>
#include <string>

namespace circular_buffer {

template <typename T>
circular_buffer<T>::circular_buffer(size_t capacity) 
    : buffer(capacity), capacity(capacity), size(0), read_pos(0), write_pos(0) {
}

template <typename T>
T circular_buffer<T>::read() {
    if (size == 0) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer[read_pos];
    read_pos = (read_pos + 1) % capacity;
    --size;
    return value;
}

template <typename T>
void circular_buffer<T>::write(const T& data) {
    if (size == capacity) {
        throw std::domain_error("Buffer is full");
    }
    buffer[write_pos] = data;
    write_pos = (write_pos + 1) % capacity;
    ++size;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& data) {
    if (size == capacity) {
        // Buffer is full, overwrite the oldest element
        buffer[write_pos] = data;
        write_pos = (write_pos + 1) % capacity;
        read_pos = (read_pos + 1) % capacity;
    } else {
        write(data);
    }
}

template <typename T>
void circular_buffer<T>::clear() {
    size = 0;
    read_pos = 0;
    write_pos = 0;
}

// Explicit instantiations
template class circular_buffer<int>;
template class circular_buffer<std::string>;

}  // namespace circular_buffer
