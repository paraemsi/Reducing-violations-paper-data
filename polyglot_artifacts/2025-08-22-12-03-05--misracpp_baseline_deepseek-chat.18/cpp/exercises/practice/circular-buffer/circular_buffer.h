#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t capacity;
    size_t count;
    size_t read_idx;
    size_t write_idx;

public:
    explicit circular_buffer(size_t capacity) 
        : buffer(capacity), capacity(capacity), count(0), read_idx(0), write_idx(0) {}
    
    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[read_idx];
        read_idx = (read_idx + 1) % capacity;
        --count;
        return value;
    }
    
    void write(const T& value) {
        if (count == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[write_idx] = value;
        write_idx = (write_idx + 1) % capacity;
        ++count;
    }
    
    void overwrite(const T& value) {
        if (count < capacity) {
            write(value);
        } else {
            buffer[write_idx] = value;
            write_idx = (write_idx + 1) % capacity;
            read_idx = (read_idx + 1) % capacity;
        }
    }
    
    void clear() {
        count = 0;
        read_idx = 0;
        write_idx = 0;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
