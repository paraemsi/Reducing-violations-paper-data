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
    size_t count;
    size_t capacity;
    bool is_buff_full;

public:
    explicit circular_buffer(size_t size) 
        : buffer(size), head(0), tail(0), count(0), capacity(size), is_buff_full(false) {
    }

    T read() {
        if (count == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        count--;
        is_buff_full = false;
        return value;
    }

    void write(const T& data) {
        if (is_buff_full) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        count++;
        if (count == capacity) {
            is_buff_full = true;
        }
    }

    void overwrite(const T& data) {
        if (is_buff_full) {
            // Overwrite the oldest element at head, then move head and tail
            buffer[tail] = data;
            tail = (tail + 1) % capacity;
            head = tail; // This maintains the buffer as full
        } else {
            write(data);
        }
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
        is_buff_full = false;
    }

    bool empty() const {
        return count == 0;
    }

    bool is_full() const {
        return is_buff_full;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
