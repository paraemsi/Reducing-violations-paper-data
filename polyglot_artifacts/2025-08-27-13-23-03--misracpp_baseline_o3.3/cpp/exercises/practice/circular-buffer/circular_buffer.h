#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <algorithm>
#include <vector>
#include <optional>
#include <stdexcept>
#include <cstddef>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_{capacity},
          buffer_(capacity),
          head_{0},
          tail_{0},
          count_{0} {
        if (capacity_ == 0) {
            throw std::invalid_argument("Capacity must be > 0");
        }
    }

    void write(const T& item) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = item;
        tail_ = next_index(tail_);
        ++count_;
    }

    void overwrite(const T& item) {
        if (is_full()) {
            // Overwrite the oldest element (pointed to by head_),
            // then advance head_ to the new oldest element.
            buffer_[head_] = item;
            head_ = next_index(head_);
            // Because the buffer is (and remains) full, tail_ must also
            // advance so that it always points at the next write position.
            tail_ = head_;
            // count_ remains unchanged (still full).
        } else {
            write(item);
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = *buffer_[head_];
        buffer_[head_] = std::nullopt;
        head_ = next_index(head_);
        --count_;
        return value;
    }

    void clear() noexcept {
        std::fill(buffer_.begin(), buffer_.end(), std::nullopt);
        head_ = tail_ = count_ = 0;
    }

    bool is_empty() const noexcept { return count_ == 0; }
    bool is_full()  const noexcept { return count_ == capacity_; }

private:
    std::size_t next_index(std::size_t index) const noexcept {
        return (index + 1) % capacity_;
    }

    const std::size_t capacity_;
    std::vector<std::optional<T>> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
