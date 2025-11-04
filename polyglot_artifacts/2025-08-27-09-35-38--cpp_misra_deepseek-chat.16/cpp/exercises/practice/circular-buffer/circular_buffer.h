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
    std::uint32_t capacity;

public:
    explicit circular_buffer(std::uint32_t size) 
        : buffer(size), head(0U), tail(0U), count(0U), capacity(size) {
    }

    T read() {
        if (count == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1U) % capacity;
        --count;
        return value;
    }

    void write(const T& data) {
        if (count == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1U) % capacity;
        ++count;
    }

    void overwrite(const T& data) {
        if (count == capacity) {
            // Move head forward to make space, effectively overwriting the oldest element
            head = (head + 1U) % capacity;
            --count;
        }
        buffer[tail] = data;
        tail = (tail + 1U) % capacity;
        ++count;
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
        return (count == capacity);
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
