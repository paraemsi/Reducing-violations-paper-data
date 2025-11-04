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
    std::uint32_t read_index;
    std::uint32_t write_index;
    std::uint32_t num_elements;
    std::uint32_t capacity;

public:
    explicit circular_buffer(std::uint32_t size) 
        : buffer(size), read_index(0U), write_index(0U), num_elements(0U), capacity(size) {
    }

    T read() {
        if (num_elements == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[read_index];
        read_index = (read_index + 1U) % capacity;
        --num_elements;
        return value;
    }

    void write(const T& data) {
        if (num_elements == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[write_index] = data;
        write_index = (write_index + 1U) % capacity;
        ++num_elements;
    }

    void overwrite(const T& data) {
        if (num_elements < capacity) {
            write(data);
        } else {
            buffer[write_index] = data;
            write_index = (write_index + 1U) % capacity;
            read_index = (read_index + 1U) % capacity;
        }
    }

    void clear() {
        read_index = 0U;
        write_index = 0U;
        num_elements = 0U;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
