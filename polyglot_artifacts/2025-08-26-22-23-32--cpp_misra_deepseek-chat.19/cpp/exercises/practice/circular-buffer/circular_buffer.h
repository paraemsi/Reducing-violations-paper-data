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
    std::size_t capacity_;

public:
    explicit circular_buffer(std::size_t capacity) 
        : buffer(capacity), head(0), tail(0), count(0), capacity_(capacity) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity_;
        count--;
        return value;
    }

    void write(const T& data) {
        if (count == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity_;
        count++;
    }

    void overwrite(const T& data) {
        if (count == capacity_) {
            // Buffer is full, we need to overwrite the oldest element which is at head
            // Write the new data to the current tail position
            buffer[tail] = data;
            // Advance both tail and head
            tail = (tail + 1) % capacity_;
            head = tail; // Since the buffer is always full, head should point to the oldest element
            // In a full buffer, head == tail, and after writing, we advance both to maintain full state
        } else {
            write(data);
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
