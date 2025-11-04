#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <vector>
#include <algorithm>   // for std::fill
#include <utility>     // for std::move

namespace circular_buffer {

/*
 * A generic fixed-capacity circular (ring) buffer.
 *
 *  - write(value)      : append value, throws std::domain_error if buffer full
 *  - overwrite(value)  : append value, overwriting the oldest element if full
 *  - read()            : remove & return oldest element, throws std::domain_error if buffer empty
 *  - clear()           : remove all elements, buffer becomes empty
 */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_{capacity},
          buffer_(capacity),
          head_{0},
          tail_{0},
          size_{0} {
        if (capacity_ == 0) {
            throw std::invalid_argument("capacity must be greater than zero");
        }
    }

    /* Append a value.  Throws std::domain_error if the buffer is full. */
    void write(const T& value) {
        if (is_full()) {
            throw std::domain_error("buffer full");
        }
        push(value);
    }

    /* Append a value, overwriting the oldest value if the buffer is full. */
    void overwrite(const T& value) {
        if (is_full()) {
            buffer_[tail_] = value;   // overwrite at tail (next write position)
            advance(tail_);           // move tail forward
            advance(head_);           // oldest element moved forward
        } else {
            push(value);
        }
    }

    /* Remove and return the oldest value.  Throws std::domain_error if empty. */
    T read() {
        if (is_empty()) {
            throw std::domain_error("buffer empty");
        }

        T value = std::move(*buffer_[head_]);
        buffer_[head_] = std::nullopt;
        advance(head_);
        --size_;
        return value;
    }

    /* Remove all elements, making the buffer empty. */
    void clear() noexcept {
        std::fill(buffer_.begin(), buffer_.end(), std::nullopt);
        head_ = tail_ = size_ = 0;
    }

    /* Convenience helpers */
    bool is_empty() const noexcept { return size_ == 0; }
    bool is_full()  const noexcept { return size_ == capacity_; }
    std::size_t size()     const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }

private:
    std::size_t capacity_;
    std::vector<std::optional<T>> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;

    /* Internal helpers */
    void advance(std::size_t& index) noexcept { index = (index + 1) % capacity_; }

    void push(const T& value) {
        buffer_[tail_] = value;
        advance(tail_);
        ++size_;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
