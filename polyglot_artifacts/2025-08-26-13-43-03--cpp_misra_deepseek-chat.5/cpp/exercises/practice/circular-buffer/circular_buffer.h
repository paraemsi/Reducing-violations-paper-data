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
    bool full;

public:
    explicit circular_buffer(std::size_t size) 
        : buffer(size), head(0U), tail(0U), count(0U), 
          capacity(static_cast<std::uint32_t>(size)), full(false) {
        if (size > static_cast<std::size_t>(UINT32_MAX)) {
            throw std::invalid_argument("Size too large");
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = ((head + 1U) % capacity);
        full = false;
        count--;
        return value;
    }

    void write(const T& data) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = ((tail + 1U) % capacity);
        count++;
        full = (count == capacity);
    }

    void overwrite(const T& data) {
        if (is_full()) {
            // Overwrite the oldest element at head, then move head
            buffer[tail] = data;
            tail = ((tail + 1U) % capacity);
            head = tail; // Since the buffer is full, head should now point to the new oldest element
        } else {
            write(data);
        }
    }

    void clear() {
        head = tail;
        count = 0U;
        full = false;
    }

    bool is_empty() const {
        return ((!full) && (head == tail));
    }

    bool is_full() const {
        return full;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
