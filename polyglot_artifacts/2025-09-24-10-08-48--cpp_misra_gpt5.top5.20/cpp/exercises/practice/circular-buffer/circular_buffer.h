#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

struct buffer_empty final : public std::domain_error {
    buffer_empty() : std::domain_error("buffer is empty") {}
};

struct buffer_full final : public std::domain_error {
    buffer_full() : std::domain_error("buffer is full") {}
};

template <typename T>
class circular_buffer final {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          head_(static_cast<std::size_t>(0U)),
          tail_(static_cast<std::size_t>(0U)),
          size_(static_cast<std::size_t>(0U)),
          capacity_(capacity) {}

    T read() {
        if ((size_ == static_cast<std::size_t>(0U))) {
            throw buffer_empty();
        } else {
            T value = buffer_[head_];
            if ((capacity_ != static_cast<std::size_t>(0U))) {
                head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
            }
            size_ = (size_ - static_cast<std::size_t>(1U));
            return value;
        }
    }

    void write(const T& value) {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw buffer_full();
        } else if ((size_ == capacity_)) {
            throw buffer_full();
        } else {
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            size_ = (size_ + static_cast<std::size_t>(1U));
        }
    }

    void overwrite(const T& value) {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            return;
        } else if ((size_ == capacity_)) {
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        } else {
            write(value);
        }
    }

    void clear() noexcept {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        size_ = static_cast<std::size_t>(0U);
    }

private:
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
    const std::size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
