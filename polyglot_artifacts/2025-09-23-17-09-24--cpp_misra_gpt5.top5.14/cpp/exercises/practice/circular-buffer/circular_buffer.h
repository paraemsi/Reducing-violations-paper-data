#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
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
          head_(static_cast<std::size_t>(0U)),
          tail_(static_cast<std::size_t>(0U)),
          size_(static_cast<std::size_t>(0U)) {
    }

    void clear() noexcept {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        size_ = static_cast<std::size_t>(0U);
    }

    bool empty() const noexcept {
        return (size_ == static_cast<std::size_t>(0U));
    }

    bool full() const noexcept {
        return (size_ == capacity_);
    }

    std::size_t capacity() const noexcept {
        return capacity_;
    }

    std::size_t size() const noexcept {
        return size_;
    }

    void write(const T& value) {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("write on zero-capacity buffer");
        }
        if (full()) {
            throw std::domain_error("write on full buffer");
        }
        buffer_[tail_] = value;
        tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ = (size_ + static_cast<std::size_t>(1U));
    }

    void write(T&& value) {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("write on zero-capacity buffer");
        }
        if (full()) {
            throw std::domain_error("write on full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ = (size_ + static_cast<std::size_t>(1U));
    }

    T read() {
        if (empty()) {
            throw std::domain_error("read on empty buffer");
        }
        T value = std::move(buffer_[head_]);
        head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ = (size_ - static_cast<std::size_t>(1U));
        return value;
    }

    void overwrite(const T& value) {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("overwrite on zero-capacity buffer");
        }
        if (full()) {
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        } else {
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            size_ = (size_ + static_cast<std::size_t>(1U));
        }
    }

    void overwrite(T&& value) {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("overwrite on zero-capacity buffer");
        }
        if (full()) {
            buffer_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        } else {
            buffer_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            size_ = (size_ + static_cast<std::size_t>(1U));
        }
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;  // index of the oldest element
    std::size_t tail_;  // index of the next write position
    std::size_t size_;  // number of elements stored
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
