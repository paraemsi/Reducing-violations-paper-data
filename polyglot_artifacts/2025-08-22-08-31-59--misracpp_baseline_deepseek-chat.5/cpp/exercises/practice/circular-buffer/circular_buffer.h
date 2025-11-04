#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;

public:
    explicit circular_buffer(size_t size) 
        : buffer(size), head(0), tail(0), count(0), capacity(size) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        count--;
        return value;
    }

    void write(const T& data) {
        if (count == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        count++;
    }

    void overwrite(const T& data) {
        if (count < capacity) {
            write(data);
        } else {
            // Write to the current head position to overwrite the oldest element
            buffer[head] = data;
            // Advance both head and tail
            head = (head + 1) % capacity;
            tail = (tail + 1) % capacity;
        }
    }

    void clear() {
        head = tail = count = 0;
    }

    bool empty() const {
        return count == 0;
    }

    bool is_full() const {
        return count == capacity;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
