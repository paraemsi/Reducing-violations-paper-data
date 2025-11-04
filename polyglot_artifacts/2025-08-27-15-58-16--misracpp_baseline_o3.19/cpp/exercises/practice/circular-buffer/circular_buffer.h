#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <algorithm>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

/*
 * A generic fixed-size ring buffer.
 *
 * push with write(), pop with read().
 * write() throws std::overflow_error  when the buffer is full.
 * read()  throws std::underflow_error when the buffer is empty.
 *
 * overwrite() always succeeds; when the buffer is full the oldest element
 * will be replaced.
 */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          full_(false) {
        if (capacity == 0) {
            throw std::invalid_argument("Circular buffer cannot have zero capacity");
        }
    }

    // Query helpers ----------------------------------------------------------
    bool empty() const noexcept { return !full_ && (head_ == tail_); }
    bool full()  const noexcept { return full_; }
    std::size_t capacity() const noexcept { return capacity_; }

    std::size_t size() const noexcept {
        if (full_) return capacity_;
        if (tail_ >= head_) {
            return tail_ - head_;
        }
        return capacity_ + tail_ - head_;
    }

    // Core operations --------------------------------------------------------
    void clear() noexcept {
        for (auto &slot : buffer_) {
            slot.reset();            // release any stored value without copying
        }
        head_ = 0;
        tail_ = 0;
        full_ = false;
    }

    T read() {
        if (empty()) {
            throw std::domain_error("Circular buffer is empty");
        }

        T value = std::move(*buffer_[head_]);
        buffer_[head_] = std::nullopt;
        advance(head_);
        full_ = false;

        return value;
    }

    template <typename U = T>
    void write(U&& value) {
        if (full()) {
            throw std::domain_error("Circular buffer is full");
        }
        buffer_[tail_] = std::forward<U>(value);
        commit_write();
    }

    template <typename U = T>
    void overwrite(U&& value) {
        if (full()) {
            buffer_[head_] = std::forward<U>(value);
            advance(head_);
            advance(tail_);
        } else {
            write(std::forward<U>(value));
        }
    }

private:
    void advance(std::size_t& index) noexcept { index = (index + 1) % capacity_; }

    void commit_write() noexcept {
        advance(tail_);
        if (tail_ == head_) {
            full_ = true;
        }
    }

    std::vector<std::optional<T>> buffer_;
    const std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    bool full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
