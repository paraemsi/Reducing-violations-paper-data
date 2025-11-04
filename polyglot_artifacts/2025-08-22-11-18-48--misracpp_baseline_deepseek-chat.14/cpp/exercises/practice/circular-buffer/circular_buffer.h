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
    size_t head;
    size_t tail;
    
public:
    explicit circular_buffer(size_t capacity) 
        : capacity(capacity), size(0), head(0), tail(0) {
        buffer.resize(capacity);
    }

    T read() {
        if (size == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        --size;
        return value;
    }

    void write(const T& data) {
        if (size == capacity) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        ++size;
    }

    void overwrite(const T& data) {
        if (size == capacity) {
            // Overwrite the oldest element by moving head forward
            buffer[tail] = data;
            tail = (tail + 1) % capacity;
            head = tail;
        } else {
            write(data);
        }
    }

    void clear() {
        size = 0;
        head = 0;
        tail = 0;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
