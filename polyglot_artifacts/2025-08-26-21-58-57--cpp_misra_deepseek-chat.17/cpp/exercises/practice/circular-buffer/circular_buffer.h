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
        if (size == 0U) {
            throw std::invalid_argument("Buffer size must be at least 1");
        }
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
        if (count < capacity) {
            write(data);
        } else {
            buffer[tail] = data;
            tail = (tail + 1U) % capacity;
            head = (head + 1U) % capacity;
        }
    }
    
    void clear() {
        head = 0U;
        tail = 0U;
        count = 0U;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
