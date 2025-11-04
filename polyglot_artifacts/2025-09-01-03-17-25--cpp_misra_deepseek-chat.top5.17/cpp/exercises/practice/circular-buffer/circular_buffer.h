#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

// Define a size type that uses fixed-width integer
using size_type = std::uint32_t;

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_type head;
    size_type tail;
    size_type count;
    size_type capacity_;

public:
    explicit circular_buffer(size_type size) 
        : buffer(size), head(0U), tail(0U), count(0U), capacity_(size) {
    }

    T read() {
        if (empty()) { 
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer[head];
        head = static_cast<size_type>((head + 1U) % capacity_);
        --count;
        return value;
    }

    void write(const T& data) {
        if (full()) { 
            throw std::domain_error("Buffer is full");
        }
        buffer[tail] = data;
        tail = static_cast<size_type>((tail + 1U) % capacity_);
        ++count;
    }

    void overwrite(const T& data) {
        if (full()) { 
            // Read to remove the oldest element
            read();
        }
        write(data);
    }

    void clear() {
        head = 0U;
        tail = 0U;
        count = 0U;
    }

    bool empty() const {
        return (count == 0U);
    }

    bool full() const {
        return (count == capacity_);
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
