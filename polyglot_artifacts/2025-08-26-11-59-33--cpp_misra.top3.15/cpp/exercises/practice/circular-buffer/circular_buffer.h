#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0U),
          tail_(0U),
          count_(0U)
    {
        if (capacity_ == 0U) {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    void write(const T& value)
    {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1U) % capacity_;
        count_ = count_ + 1U;
    }

    void overwrite(const T& value)
    {
        if (is_full()) {
            buffer_[tail_] = value;
            tail_ = (tail_ + 1U) % capacity_;
            head_ = (head_ + 1U) % capacity_;
        } else {
            write(value);
        }
    }

    T read()
    {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1U) % capacity_;
        count_ = count_ - 1U;
        return value;
    }

    void clear()
    {
        head_ = 0U;
        tail_ = 0U;
        count_ = 0U;
    }

    bool is_empty() const
    {
        return (count_ == 0U);
    }

    bool is_full() const
    {
        return (count_ == capacity_);
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
