#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_{capacity},
          buffer_(capacity),
          head_{static_cast<std::size_t>(0U)},
          tail_{static_cast<std::size_t>(0U)},
          size_{static_cast<std::size_t>(0U)}
    {
        // capacity_ and buffer_ initialised
    }

    T read()
    {
        if ((size_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("empty buffer");
        }
        T value = buffer_.at(head_);
        if ((capacity_ != static_cast<std::size_t>(0U))) {
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        }
        size_ -= static_cast<std::size_t>(1U);
        return value;
    }

    void write(const T& item)
    {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("full buffer");
        }
        if ((size_ == capacity_)) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = item;
        tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ += static_cast<std::size_t>(1U);
    }

    void overwrite(const T& item)
    {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("full buffer");
        }
        if ((size_ == capacity_)) {
            buffer_[tail_] = item;
            tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
            // size_ remains equal to capacity_
            return;
        }
        write(item);
    }

    void clear()
    {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        size_ = static_cast<std::size_t>(0U);
    }

private:
    std::size_t capacity_;
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
