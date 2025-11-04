#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    using size_type = std::uint32_t;
    
    std::vector<T> buffer;
    size_type head;
    size_type tail;
    size_type count;
    size_type capacity_;

public:
    explicit circular_buffer(size_type capacity) 
        : buffer(capacity), head(0U), tail(0U), count(0U), capacity_(capacity) {
        if (capacity == 0U) {
            throw std::invalid_argument("Capacity must be at least 1");
        }
    }

    T read() {
        if (count == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = static_cast<size_type>((head + 1U) % capacity_);
        --count;
        return value;
    }

    void write(const T& data) {
        if (count == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = static_cast<size_type>((tail + 1U) % capacity_);
        ++count;
    }

    void overwrite(const T& data) {
        if (count == capacity_) {
            // Make space by moving head forward
            head = static_cast<size_type>((head + 1U) % capacity_);
            --count;
        }
        buffer[tail] = data;
        tail = static_cast<size_type>((tail + 1U) % capacity_);
        ++count;
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
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
