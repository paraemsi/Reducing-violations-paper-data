#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t capacity;
    bool full;

public:
    explicit circular_buffer(size_t size) : 
        buffer(size), head(0), tail(0), capacity(size), full(false) {}
    
    T read() {
        if (head == tail && !full) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        full = false;
        return value;
    }
    
    void write(const T& value) {
        if (full) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        // Check if the buffer is now full
        full = (head == tail);
    }
    
    void overwrite(const T& value) {
        if (full) {
            // Overwrite the oldest element at head
            buffer[head] = value;
            head = (head + 1) % capacity;
            tail = (tail + 1) % capacity;
        } else {
            write(value);
        }
    }
    
    void clear() {
        head = 0;
        tail = 0;
        full = false;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
