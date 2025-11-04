#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

typedef std::size_t size_type;

template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(size_type capacity)
        : buffer_(capacity), capacity_(capacity), head_(0U), tail_(0U), count_(0U)
    {
    }

    void write(const T& item)
    {
        if (is_full())
        {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = item;
        tail_ = (tail_ + 1U) % capacity_;
        count_ = count_ + 1U;
    }

    void overwrite(const T& item)
    {
        if (is_full())
        {
            buffer_[tail_] = item;
            tail_ = (tail_ + 1U) % capacity_;
            head_ = (head_ + 1U) % capacity_;
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
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1U) % capacity_;
        count_ = count_ - 1U;
        return value;
    }

    bool is_empty() const
    {
        return (count_ == 0U);
    }

    bool is_full() const
    {
        return (count_ == capacity_);
    }

    void clear()
    {
        head_ = 0U;
        tail_ = 0U;
        count_ = 0U;
    }

private:
    std::vector<T> buffer_;
    size_type capacity_;
    size_type head_;
    size_type tail_;
    size_type count_;
};

} // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
