#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <string>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    std::uint64_t read_pos;
    std::uint64_t write_pos;
    std::uint64_t count;
    std::uint64_t capacity;

public:
    explicit circular_buffer(std::uint64_t size) 
        : buffer(size), read_pos(0U), write_pos(0U), count(0U), capacity(size) {
    }

    T read() {
        if (count == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[read_pos];
        read_pos = (read_pos + 1U) % capacity;
        --count;
        return value;
    }

    void write(const T& data) {
        if (count == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[write_pos] = data;
        write_pos = (write_pos + 1U) % capacity;
        ++count;
    }

    void overwrite(const T& data) {
        if (count == capacity) {
            // Buffer is full, so we need to advance read_pos to "remove" the oldest element
            read_pos = (read_pos + 1U) % capacity;
            --count;
        }
        // Now we can write normally
        write(data);
    }

    void clear() {
        read_pos = 0U;
        write_pos = 0U;
        count = 0U;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
