#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t capacity;
    size_t size;
    size_t read_pos;
    size_t write_pos;

public:
    explicit circular_buffer(size_t capacity) 
        : buffer(capacity), capacity(capacity), size(0), read_pos(0), write_pos(0) {}
    
    T read() {
        if (size == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[read_pos];
        read_pos = (read_pos + 1) % capacity;
        size--;
        return value;
    }
    
    void write(const T& value) {
        if (size == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[write_pos] = value;
        write_pos = (write_pos + 1) % capacity;
        size++;
    }
    
    void overwrite(const T& value) {
        if (size < capacity) {
            write(value);
        } else {
            buffer[write_pos] = value;
            write_pos = (write_pos + 1) % capacity;
            read_pos = (read_pos + 1) % capacity;
        }
    }
    
    void clear() {
        size = 0;
        read_pos = 0;
        write_pos = 0;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
