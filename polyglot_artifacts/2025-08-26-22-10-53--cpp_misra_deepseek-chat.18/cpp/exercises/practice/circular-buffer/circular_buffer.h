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
    std::uint32_t read_pos;
    std::uint32_t write_pos;
    std::uint32_t count;
    std::uint32_t capacity;
    
public:
    explicit circular_buffer(std::uint32_t size) 
        : buffer(size), read_pos(0), write_pos(0), count(0), capacity(size) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T data = buffer[read_pos];
        read_pos = ((read_pos + 1U) % capacity);
        --count;
        return data;
    }

    void write(const T& data) {
        if (count == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[write_pos] = data;
        write_pos = ((write_pos + 1U) % capacity);
        ++count;
    }

    void overwrite(const T& data) {
        if (count < capacity) {
            write(data);
        } else {
            buffer[write_pos] = data;
            write_pos = ((write_pos + 1U) % capacity);
            read_pos = ((read_pos + 1U) % capacity);
        }
    }

    void clear() {
        read_pos = 0;
        write_pos = 0;
        count = 0;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
