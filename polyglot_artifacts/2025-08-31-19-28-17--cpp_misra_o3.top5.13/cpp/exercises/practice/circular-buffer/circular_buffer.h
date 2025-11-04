#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

namespace circular_buffer {

template <typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::size_t capacity)
        : data_(capacity), head_(0U), tail_(0U), full_(false)
    {
        if (capacity == 0U)
        {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    void clear() noexcept
    {
        head_ = 0U;
        tail_ = 0U;
        full_ = false;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return ((full_ == false) && (head_ == tail_));
    }

    [[nodiscard]] bool full() const noexcept
    {
        return full_;
    }

    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return data_.size();
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        if (full_ != false)
        {
            return data_.size();
        }

        if (head_ >= tail_)
        {
            return (head_ - tail_);
        }
        else
        {
            return (data_.size() - (tail_ - head_));
        }
    }

    void write(const T& item)
    {
        if (full_ != false)
        {
            throw std::domain_error("Buffer is full");
        }

        data_[head_] = item;
        advance_head();
    }

    void overwrite(const T& item)
    {
        if (full_ != false)
        {
            /* buffer is full – overwrite oldest element */
            data_[head_] = item;

            /* advance both head and tail to next slot to maintain the buffer in a full state */
            head_ = (head_ + 1U) % data_.size();
            tail_ = head_;
            full_ = true;
        }
        else
        {
            write(item);
        }
    }

    T read()
    {
        if (empty() != false)
        {
            throw std::domain_error("Buffer is empty");
        }

        T value = data_[tail_];
        advance_tail();
        return value;
    }

private:
    void advance_head()
    {
        head_ = (head_ + 1U) % data_.size();
        if (head_ == tail_)
        {
            full_ = true;
        }
    }

    void advance_tail()
    {
        full_ = false;
        tail_ = (tail_ + 1U) % data_.size();
    }

    std::vector<T> data_;
    std::size_t head_;
    std::size_t tail_;
    bool full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
