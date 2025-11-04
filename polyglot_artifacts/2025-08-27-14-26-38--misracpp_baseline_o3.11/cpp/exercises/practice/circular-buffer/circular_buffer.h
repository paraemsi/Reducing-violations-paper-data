#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <utility>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : head_(0), tail_(0), size_(0), capacity_(capacity), buffer_(capacity) {
        if (capacity_ == 0) {
            throw std::domain_error("capacity must be > 0");
        }
    }

    // Write a value when space is available, otherwise throw.
    void write(const T& value) {
        if (is_full()) {
            throw std::domain_error("buffer is full");
        }
        push(value);
    }

    void write(T&& value) {
        if (is_full()) {
            throw std::domain_error("buffer is full");
        }
        push(std::move(value));
    }

    // Read and remove the oldest value, otherwise throw.
    T read() {
        if (is_empty()) {
            throw std::domain_error("buffer is empty");
        }
        T value = buffer_[head_];
        head_ = next(head_);
        --size_;
        return value;
    }

    // Overwrite the oldest value when full, otherwise behave like write.
    void overwrite(const T& value) {
        if (is_full()) {
            pop();            // discard oldest
        }
        push(value);
    }

    void overwrite(T&& value) {
        if (is_full()) {
            pop();
        }
        push(std::move(value));
    }

    // Clear the buffer to the initial empty state.
    void clear() noexcept {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

private:
    bool is_empty() const noexcept { return size_ == 0; }
    bool is_full() const noexcept { return size_ == capacity_; }

    std::size_t next(std::size_t index) const noexcept {
        return (index + 1) % capacity_;
    }

    template <typename U>
    void push(U&& value) {
        buffer_[tail_] = std::forward<U>(value);
        tail_ = next(tail_);
        ++size_;
    }

    void pop() {
        head_ = next(head_);
        --size_;
    }

    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
    std::size_t capacity_;
    std::vector<T> buffer_;
};

} // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
