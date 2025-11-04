#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstdint>

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
        read_pos = ((read_pos + 1U) % capacity);
        --count;
        return value;
    }

    void write(const T& value) {
        if (count == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[write_pos] = value;
        write_pos = ((write_pos + 1U) % capacity);
        ++count;
    }

    void overwrite(const T& value) {
        if (count < capacity) {
            write(value);
        } else {
            buffer[write_pos] = value;
            write_pos = ((write_pos + 1U) % capacity);
            read_pos = ((read_pos + 1U) % capacity);
        }
    }

    void clear() {
        read_pos = 0U;
        write_pos = 0U;
        count = 0U;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
