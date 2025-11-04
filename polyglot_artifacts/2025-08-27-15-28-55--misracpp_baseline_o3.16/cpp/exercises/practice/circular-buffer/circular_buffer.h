#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace circular_buffer {

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
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    void clear() noexcept {
        head_ = tail_ = size_ = 0;
    }

    bool is_empty() const noexcept { return size_ == 0; }
    bool is_full()  const noexcept { return size_ == capacity_; }

    void write(const T& value) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = value;
        tail_ = advance(tail_);
        ++size_;
    }

    // Overload accepting rvalue to enable move semantics
    void write(T&& value) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = std::move(value);
        tail_ = advance(tail_);
        ++size_;
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = std::move(buffer_[head_]);
        head_ = advance(head_);
        --size_;
        return value;
    }

    void overwrite(const T& value) {
        if (is_full()) {
            buffer_[head_] = value;           // overwrite oldest
            head_ = advance(head_);           // advance head to new oldest
            tail_ = head_;                    // keep tail in sync
        } else {
            write(value);
        }
    }

    // Overload accepting rvalue for overwrite as well
    void overwrite(T&& value) {
        if (is_full()) {
            buffer_[head_] = std::move(value); // overwrite oldest
            head_ = advance(head_);            // advance head to new oldest
            tail_ = head_;                     // keep tail in sync
        } else {
            write(std::move(value));
        }
    }

private:
    std::size_t advance(std::size_t index) const noexcept {
        return (index + 1) % capacity_;
    }

    const std::size_t capacity_;
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
