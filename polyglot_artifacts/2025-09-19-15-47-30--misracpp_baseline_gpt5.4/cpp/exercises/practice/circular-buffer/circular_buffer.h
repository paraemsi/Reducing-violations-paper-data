#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          size_(0) {}

    // Remove and return the oldest element. Throws if buffer is empty.
    T read() {
        if (empty()) {
            throw std::domain_error("buffer empty");
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    // Write a new element. Throws if buffer is full.
    void write(const T& value) {
        if (full()) {
            throw std::domain_error("buffer full");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    // Move-overload for efficiency with movable types.
    void write(T&& value) {
        if (full()) {
            throw std::domain_error("buffer full");
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    // Write a new element. If full, overwrite the oldest element.
    void overwrite(const T& value) {
        overwrite_impl(value);
    }

    // Move-overload for overwrite.
    void overwrite(T&& value) {
        overwrite_impl(std::move(value));
    }

    // Clear the buffer to the empty state.
    void clear() noexcept {
        head_ = tail_ = size_ = 0;
    }

    // Optional helpers.
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }
    bool full() const noexcept { return size_ == capacity_; }

private:
    template <typename U>
    void overwrite_impl(U&& value) {
        if (capacity_ == 0) {
            return;  // Degenerate capacity; nothing to do.
        }
        buffer_[tail_] = std::forward<U>(value);
        if (full()) {
            // Drop the oldest element by advancing head.
            head_ = (head_ + 1) % capacity_;
        } else {
            ++size_;
        }
        tail_ = (tail_ + 1) % capacity_;
    }

    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;  // Index of the oldest element.
    std::size_t tail_;  // Index of the next write position.
    std::size_t size_;  // Current number of stored elements.
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
