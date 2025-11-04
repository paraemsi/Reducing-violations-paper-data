#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <cstddef>
#include <stdexcept>

namespace circular_buffer {

template<typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t capacity;
    size_t size_;
    size_t head;
    size_t tail;

public:
    circular_buffer(size_t cap) : capacity(cap), size_(0), head(0), tail(0), buffer(cap) {}

    void write(T value) {
        if (size_ == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        size_++;
    }

    void overwrite(T value) {
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        if (size_ == capacity) {
            head = (head + 1) % capacity;
        } else {
            size_++;
        }
    }

    T read() {
        if (size_ == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        size_--;
        return value;
    }

    void clear() {
        size_ = 0;
        head = 0;
        tail = 0;
    }

    bool is_empty() const {
        return size_ == 0;
    }

    bool is_full() const {
        return size_ == capacity;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
