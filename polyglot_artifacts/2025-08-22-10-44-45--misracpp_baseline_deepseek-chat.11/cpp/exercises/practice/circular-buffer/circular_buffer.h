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
    explicit circular_buffer(size_t size) 
        : buffer(size), head(0), tail(0), capacity(size), full(false) {
    }

    T read() {
        if (empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        full = false;
        return value;
    }

    void write(const T& data) {
        if (full) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        full = (tail == head);
    }

    void overwrite(const T& data) {
        if (full) {
            // Read and discard the oldest element to make space
            // This will advance head and set full to false
            read();
        }
        // Write the new data
        write(data);
    }

    void clear() {
        head = 0;
        tail = 0;
        full = false;
    }

    bool empty() const {
        return (!full && (head == tail));
    }

    bool is_full() const {
        return full;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
