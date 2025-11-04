#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>      // fixed-width integer types per MISRA guidance
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/*
 * Fixed-capacity circular buffer that stores values of type T.
 * All member functions have constant complexity.
 *
 * MISRA C++ compliance notes:
 * - Uses std::size_t for all indexing to avoid introducing
 *   standard signed / unsigned integer type names directly.
 * - Explicit parentheses are added around sub-expressions
 *   wherever operator precedence could be ambiguous.
 * - Every if / else body is a compound statement.
 */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity) :
        buffer_(capacity),
        max_size_(capacity)
    {
        if (capacity == static_cast<std::size_t>(0U)) {
            throw std::domain_error("capacity must be > 0");
        }
    }

    void write(const T& value)
    {
        if (full_) {
            throw std::domain_error("buffer is full");
        }

        buffer_[tail_] = value;
        tail_ = ( (tail_ + static_cast<std::size_t>(1U)) % max_size_ );

        if (tail_ == head_) {
            full_ = true;
        }
    }

    void overwrite(const T& value)
    {
        if (full_) {
            /* discard oldest element first */
            head_ = ( (head_ + static_cast<std::size_t>(1U)) % max_size_ );
            full_ = false;
        }

        write(value);
    }

    T read()
    {
        if (empty()) {
            throw std::domain_error("buffer is empty");
        }

        T value = buffer_[head_];
        head_ = ( (head_ + static_cast<std::size_t>(1U)) % max_size_ );
        full_ = false;
        return value;
    }

    void clear() noexcept
    {
        head_ = tail_;
        full_ = false;
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        if (full_) {
            return max_size_;
        }

        if (tail_ >= head_) {
            return ( tail_ - head_ );
        }

        return ( max_size_ + tail_ - head_ );
    }

    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return max_size_;
    }

private:
    [[nodiscard]] bool empty() const noexcept
    {
        return ( (!full_) && (head_ == tail_) );
    }

    std::vector<T> buffer_;
    std::size_t     head_{0U};
    std::size_t     tail_{0U};
    std::size_t     max_size_{0U};
    bool            full_{false};
};

/* Provide the previously-used PascalCase alias so either spelling works. */
template <typename T>
using CircularBuffer = circular_buffer<T>;

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
