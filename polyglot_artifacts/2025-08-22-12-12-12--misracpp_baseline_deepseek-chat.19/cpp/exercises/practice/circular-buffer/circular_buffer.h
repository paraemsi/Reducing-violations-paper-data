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
    
public:
    explicit circular_buffer(size_t capacity) 
        : buffer(capacity), head(0), tail(0), count(0), capacity_(capacity) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity_;
        count--;
        return value;
    }

    void write(const T& data) {
        if (count == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity_;
        count++;
    }

    void overwrite(const T& data) {
        if (count == capacity_) {
            // Overwrite the element at head, then advance both pointers
            buffer[tail] = data;
            tail = (tail + 1) % capacity_;
            head = (head + 1) % capacity_;
        } else {
            write(data);
        }
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
