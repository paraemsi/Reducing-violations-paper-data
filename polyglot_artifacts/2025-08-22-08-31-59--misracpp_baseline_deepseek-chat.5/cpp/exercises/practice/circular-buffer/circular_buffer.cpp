#include "circular_buffer.h"
#include <stdexcept>
#include <algorithm>

namespace circular_buffer {

circular_buffer::circular_buffer(size_t size) 
    : capacity(size), head(0), tail(0), count(0) {
    buffer = new int[capacity];
}

circular_buffer::~circular_buffer() {
    delete[] buffer;
}

int circular_buffer::read() {
    if (count == 0) {
        throw std::domain_error("Buffer is empty");
    }
    int value = buffer[head];
    head = (head + 1) % capacity;
    count--;
    return value;
}

void circular_buffer::write(int data) {
    if (count == capacity) {
        throw std::domain_error("Buffer is full");
    }
    buffer[tail] = data;
    tail = (tail + 1) % capacity;
    count++;
}

void circular_buffer::overwrite(int data) {
    if (count < capacity) {
        write(data);
    } else {
        buffer[head] = data;
        head = (head + 1) % capacity;
        tail = (tail + 1) % capacity;
        // head and tail move together when overwriting while full
        // This ensures the oldest element is always at head
    }
}

void circular_buffer::clear() {
    head = tail = count = 0;
}

bool circular_buffer::is_empty() const {
    return count == 0;
}

bool circular_buffer::is_full() const {
    return count == capacity;
}

}  // namespace circular_buffer
