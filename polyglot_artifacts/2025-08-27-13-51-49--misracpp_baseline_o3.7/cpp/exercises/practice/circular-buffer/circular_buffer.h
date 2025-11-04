#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <optional>
#include <cstddef>
#include <stdexcept>
#include <algorithm>  // for std::fill

namespace circular_buffer {

// Exceptions -----------------------------------------------------------------
struct buffer_full : std::domain_error {
    buffer_full() : std::domain_error("circular buffer is full") {}
};

struct buffer_empty : std::domain_error {
    buffer_empty() : std::domain_error("circular buffer is empty") {}
};

// Circular buffer ------------------------------------------------------------
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          head_(0),
          tail_(0),
          size_(0),
          capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("circular buffer capacity must be greater than 0");
        }
    }

    // Remove all elements from the buffer.
    void clear() noexcept {
        head_ = tail_ = size_ = 0;
        std::fill(buffer_.begin(), buffer_.end(), std::nullopt);
    }

    // Query state ------------------------------------------------------------
    bool empty() const noexcept { return size_ == 0; }
    bool full()  const noexcept { return size_ == capacity_; }

    // Alternate query names often used by tests
    bool is_empty() const noexcept { return empty(); }
    bool is_full()  const noexcept { return full(); }

    // Additional helpers -----------------------------------------------------
    std::size_t size()     const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }

    // Read and write ---------------------------------------------------------
    T read() {
        if (empty()) {
            throw buffer_empty();
        }
        T value = *buffer_[tail_];
        buffer_[tail_] = std::nullopt;
        tail_ = (tail_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& item) {
        if (full()) {
            throw buffer_full();
        }
        buffer_[head_] = item;
        head_ = (head_ + 1) % capacity_;
        ++size_;
    }

    // Write, replacing the oldest element when the buffer is full.
    void overwrite(const T& item) {
        if (full()) {
            buffer_[tail_] = item;               // replace oldest
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;     // advance head in lock-step
        } else {
            write(item);
        }
    }

private:
    std::vector<std::optional<T>> buffer_;
    std::size_t    head_;      // next position to write
    std::size_t    tail_;      // next position to read
    std::size_t    size_;      // current number of stored elements
    std::size_t    capacity_;  // fixed capacity
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
