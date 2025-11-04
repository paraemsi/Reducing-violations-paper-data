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
    std::uint32_t head;
    std::uint32_t tail;
    std::uint32_t count;
    std::uint32_t capacity_;

public:
    explicit circular_buffer(std::uint32_t size) 
        : buffer(size), head(0), tail(0), count(0), capacity_(size) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1U) % capacity_;
        count--;
        return value;
    }

    void write(const T& value) {
        if (count == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = value;
        tail = (tail + 1U) % capacity_;
        count++;
    }

    void overwrite(const T& value) {
        if (count == capacity_) {
            // Buffer is full, overwrite the oldest element (at head)
            buffer[tail] = value;
            tail = (tail + 1U) % capacity_;
            // Move head to the next position as the oldest element is now overwritten
            head = tail;
        } else {
            write(value);
        }
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
