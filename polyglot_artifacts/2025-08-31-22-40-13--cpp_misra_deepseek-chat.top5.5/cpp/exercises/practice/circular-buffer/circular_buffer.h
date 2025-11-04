#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    T* buffer;
    std::uint32_t capacity;
    std::uint32_t read_pos;
    std::uint32_t write_pos;
    std::uint32_t count;
    
public:
    explicit circular_buffer(std::uint32_t size) 
        : capacity(size), read_pos(0U), write_pos(0U), count(0U) {
        buffer = new T[capacity];
    }
    
    ~circular_buffer() {
        delete[] buffer;
    }
    
    T read() {
        if (is_empty()) { 
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[read_pos];
        read_pos = ((read_pos + 1U) % capacity);
        --count;
        return value;
    }
    
    void write(const T& data) {
        if (is_full()) { 
            throw std::domain_error("Buffer is full");
        }
        buffer[write_pos] = data;
        write_pos = ((write_pos + 1U) % capacity);
        ++count;
    }
    
    void overwrite(const T& data) {
        if (is_full()) { 
            // Overwrite the oldest element
            buffer[write_pos] = data;
            write_pos = ((write_pos + 1U) % capacity);
            read_pos = ((read_pos + 1U) % capacity);
        } else { 
            write(data);
        }
    }
    
    void clear() {
        read_pos = 0U;
        write_pos = 0U;
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
