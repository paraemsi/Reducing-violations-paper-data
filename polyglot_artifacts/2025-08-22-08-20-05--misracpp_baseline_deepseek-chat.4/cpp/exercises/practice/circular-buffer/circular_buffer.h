#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity_;
    
    bool full() const {
        return count == capacity_;
    }
    bool empty() const {
        return count == 0;
    }

public:
    explicit circular_buffer(size_t size) 
        : buffer(size), head(0), tail(0), count(0), capacity_(size) {
    }
    
    T read() {
        if (empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity_;
        --count;
        return value;
    }
    
    void write(const T& data) {
        if (full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity_;
        ++count;
    }
    
    void overwrite(const T& data) {
        if (full()) {
            // Write the new data to the current tail position
            buffer[tail] = data;
            // Move tail forward
            tail = (tail + 1) % capacity_;
            // Head must also move forward to point to the new oldest element
            head = tail;
        } else {
            write(data);
        }
    }
    
    void clear() {
        head = tail = count = 0;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
