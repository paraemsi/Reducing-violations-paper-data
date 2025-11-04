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
    explicit circular_buffer(std::size_t size) 
        : buffer(size), head(0U), tail(0U), count(0U), capacity(static_cast<std::uint32_t>(size)) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = static_cast<std::uint32_t>(((head + 1U)) % capacity);
        --count;
        return value;
    }

    void write(const T& data) {
        if (count == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = static_cast<std::uint32_t>(((tail + 1U)) % capacity);
        ++count;
    }

    void overwrite(const T& data) {
        if (count == capacity) {
            // Buffer is full, advance head to make space
            head = static_cast<std::uint32_t>(((head + 1U)) % capacity);
            // Write the data at the current tail position
            buffer[tail] = data;
            tail = static_cast<std::uint32_t>(((tail + 1U)) % capacity);
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
