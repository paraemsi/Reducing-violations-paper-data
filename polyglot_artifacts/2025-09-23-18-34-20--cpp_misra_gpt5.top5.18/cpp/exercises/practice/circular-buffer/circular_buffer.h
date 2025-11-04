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
        if ((capacity_) == static_cast<std::size_t>(0U)) {
            throw std::invalid_argument("circular_buffer capacity must be > 0");
        }
    }

    T read() {
        if ((size_) == static_cast<std::size_t>(0U)) {
            throw std::domain_error("empty buffer");
        }
        T value = std::move(buffer_[head_]);
        head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ = (size_ - static_cast<std::size_t>(1U));
        return value;
    }

    void write(const T& value) {
        if ((size_) == capacity_) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = value;
        tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ = (size_ + static_cast<std::size_t>(1U));
    }

    void write(T&& value) {
        if ((size_) == capacity_) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ = (size_ + static_cast<std::size_t>(1U));
    }

    void overwrite(const T& value) {
        if ((size_) == capacity_) {
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
        if ((size_) == capacity_) {
            buffer_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        } else {
            write(std::move(value));
        }
    }

    void clear() noexcept {
        for (std::size_t i = static_cast<std::size_t>(0U); (i < capacity_); i = (i + static_cast<std::size_t>(1U))) {
            buffer_[i] = T{};
        }
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        size_ = static_cast<std::size_t>(0U);
    }

private:
    std::vector<T> buffer_;
    const std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
