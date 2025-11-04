#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    std::size_t head;
    std::size_t tail;
    std::size_t count;
    std::size_t capacity;
    bool full;

public:
    explicit circular_buffer(std::size_t size) 
        : buffer(size), head(0), tail(0), count(0), capacity(size), full(false) {
    }

    void write(const T& data) {
        if (full) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        ++count;
        if (count == capacity) {
            full = true;
        }
    }

    void overwrite(const T& data) {
        if (full) {
            // Overwrite the oldest element which is at head
            head = (head + 1) % capacity;
            --count;
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        ++count;
        if (count == capacity) {
            full = true;
        } else {
            full = false;
        }
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        --count;
        full = false;
        return value;
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
        full = false;
    }

    bool is_empty() const {
        return (count == 0);
    }

    bool is_full() const {
        return full;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
