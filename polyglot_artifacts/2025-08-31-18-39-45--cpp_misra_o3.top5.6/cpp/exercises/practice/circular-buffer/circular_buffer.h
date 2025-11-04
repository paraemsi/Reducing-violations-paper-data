#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <vector>
#include <stdexcept>

namespace circular_buffer {

template<typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(static_cast<std::size_t>(0U)),
          tail_(static_cast<std::size_t>(0U)),
          full_(false)
    {
        if (capacity == static_cast<std::size_t>(0U))
        {
            throw std::domain_error("capacity must be greater than 0");
        }
    }

    void clear() noexcept
    {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        full_ = false;
    }

    void write(const T& item)
    {
        if (is_full())
        {
            throw std::domain_error("buffer is full");
        }

        buffer_[tail_] = item;
        tail_ = advance(tail_);

        if (tail_ == head_)
        {
            full_ = true;
        }
    }

    void overwrite(const T& item)
    {
        if (is_full())
        {
            head_ = advance(head_);
            full_ = false;
        }
        write(item);
    }

    T read()
    {
        if (is_empty())
        {
            throw std::domain_error("buffer is empty");
        }

        T value = buffer_[head_];
        head_ = advance(head_);
        full_ = false;
        return value;
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (!full_) && (head_ == tail_);
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return full_;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    bool full_;

    [[nodiscard]] std::size_t advance(std::size_t index) const noexcept
    {
        return (index + static_cast<std::size_t>(1U)) % capacity_;
    }
};
template<typename T>
using CircularBuffer = circular_buffer<T>;

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
