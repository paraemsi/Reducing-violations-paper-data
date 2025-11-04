#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;
    bool full;

public:
    explicit circular_buffer(size_t size) : 
        buffer(size), head(0), tail(0), count(0), capacity(size), full(false) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        count--;
        full = false;
        return value;
    }

    void write(const T& data) {
        if (full) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        count++;
        if (count == capacity) {
            full = true;
        }
    }

    void overwrite(const T& data) {
        if (full) {
            // Write at the current tail position, which is where head is when full
            buffer[tail] = data;
            // Advance tail to next position
            tail = (tail + 1) % capacity;
            // Head needs to move to the next position as well, since we overwrote the oldest element
            head = tail;
        } else {
            write(data);
        }
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
        full = false;
    }

    bool empty() const {
        return count == 0;
    }

    bool is_full() const {
        return full;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
