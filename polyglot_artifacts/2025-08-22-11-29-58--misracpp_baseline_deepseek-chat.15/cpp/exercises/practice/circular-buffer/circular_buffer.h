#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(size_t capacity) 
        : buffer(capacity), head(0), tail(0), count(0), capacity_(capacity) {
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity_;
        count--;
        return value;
    }

    void write(const T& data) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity_;
        count++;
    }

    void overwrite(const T& data) {
        if (is_full()) {
            // Overwrite the oldest element which is at head, then adjust
            buffer[tail] = data;
            tail = (tail + 1) % capacity_;
            head = tail; // Since it's full, head should now point to the next oldest element
        } else {
            write(data);
        }
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
    }

    bool is_empty() const {
        return count == 0;
    }

    bool is_full() const {
        return count == capacity_;
    }
    
private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
