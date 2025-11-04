#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/* Circular buffer implementation */

template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity) :
        buffer_(capacity),
        capacity_(capacity),
        head_(0U),
        tail_(0U),
        size_(0U)
    {
        if (capacity_ == 0U)
        {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    void clear()
    {
        head_ = 0U;
        tail_ = 0U;
        size_ = 0U;
    }

    bool is_empty() const
    {
        return (size_ == 0U);
    }

    bool is_full() const
    {
        return (size_ == capacity_);
    }

    void write(const T& item)
    {
        if (is_full())
        {
            throw std::domain_error("cannot write to full buffer");
        }

        buffer_[tail_] = item;
        tail_ = ((tail_ + static_cast<std::size_t>(1)) % capacity_);
        ++size_;
    }

    void overwrite(const T& item)
    {
        if (is_full())
        {
            /* Overwrite the oldest element */
            buffer_[head_] = item;
            head_ = ((head_ + static_cast<std::size_t>(1)) % capacity_);
            tail_ = head_;
        }
        else
        {
            write(item);
        }
    }

    T read()
    {
        if (is_empty())
        {
            throw std::domain_error("cannot read from empty buffer");
        }

        T value = buffer_[head_];
        head_ = ((head_ + static_cast<std::size_t>(1)) % capacity_);
        --size_;
        return value;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
