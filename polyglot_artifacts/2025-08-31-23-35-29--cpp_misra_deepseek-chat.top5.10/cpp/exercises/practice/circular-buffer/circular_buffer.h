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
    explicit circular_buffer(const std::uint32_t size) 
        : buffer(size), head(0U), tail(0U), count(0U), capacity_(size) {
    }

    void write(const T& value) {
        if (count == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = value;
        tail = ((tail + 1U) % capacity_);
        ++count;
    }

    void overwrite(const T& value) {
        if (count < capacity_) {
            write(value);
        } else {
            // Buffer is full, write to tail which is where the next element would be written
            buffer[tail] = value;
            tail = ((tail + 1U) % capacity_);
            // Advance head to point to the new oldest element
            head = tail;
        }
    }

    T read() {
        if (count == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = ((head + 1U) % capacity_);
        --count;
        return value;
    }

    void clear() {
        head = 0U;
        tail = 0U;
        count = 0U;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
