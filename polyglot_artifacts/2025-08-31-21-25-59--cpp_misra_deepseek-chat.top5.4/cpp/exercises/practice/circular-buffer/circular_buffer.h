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
    std::uint32_t capacity_;

public:
    explicit circular_buffer(std::uint32_t size) 
        : buffer(size), head(0U), tail(0U), count(0U), capacity_(size) {
    }

    T read() {
        if (is_empty()) { 
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = ((head + 1U) % capacity_);
        count = (count - 1U);
        return value;
    }

    void write(const T& data) {
        if (is_full()) { 
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = ((tail + 1U) % capacity_);
        count = (count + 1U);
    }

    void overwrite(const T& data) {
        if (is_full()) { 
            // Move head forward, effectively discarding the oldest element
            head = ((head + 1U) % capacity_);
            count = (count - 1U);
        }
        write(data);
    }

    void clear() {
        head = 0U;
        tail = 0U;
        count = 0U;
    }

    bool is_empty() const {
        return (count == 0U);
    }

    bool is_full() const {
        return (count == capacity_);
    }

    std::uint32_t capacity() const {
        return capacity_;
    }

    std::uint32_t size() const {
        return count;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
