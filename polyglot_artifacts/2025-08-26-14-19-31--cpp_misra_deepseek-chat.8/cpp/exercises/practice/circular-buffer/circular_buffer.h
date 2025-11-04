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
        : buffer(size), head(0U), tail(0U), count(0U), capacity_(size) {
    }

    T read() {
        if (count == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = static_cast<std::uint32_t>((head + 1U) % capacity_);
        count--;
        return value;
    }

    void write(const T& data) {
        if (count == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = static_cast<std::uint32_t>((tail + 1U) % capacity_);
        count++;
    }

    void overwrite(const T& data) {
        if (count < capacity_) {
            write(data);
        } else {
            // Buffer is full, overwrite the oldest element at head
            buffer[tail] = data;
            // Move tail forward
            tail = static_cast<std::uint32_t>((tail + 1U) % capacity_);
            // Head needs to move forward because we're overwriting the oldest element
            head = tail;
        }
    }

    void clear() {
        head = 0U;
        tail = 0U;
        count = 0U;
    }

    bool is_empty() const {
        return (count == 0U);
    }

    bool is_full() const {
        return (count == capacity_);
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
