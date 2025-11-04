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
        if (is_full()) {
            // Write the data at the current tail, which will overwrite the oldest element
            buffer[tail] = data;
            // Move both head and tail forward
            head = (head + 1) % capacity_;
            tail = (tail + 1) % capacity_;
        } else {
            write(data);
        }
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
    }

    bool is_empty() const {
        return count == 0;
    }

    bool is_full() const {
        return count == capacity_;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
