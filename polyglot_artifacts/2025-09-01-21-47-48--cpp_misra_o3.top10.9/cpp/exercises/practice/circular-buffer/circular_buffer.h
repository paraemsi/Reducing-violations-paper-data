#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <cstdint>
#include <string>

namespace circular_buffer {

class buffer_error final : public std::domain_error
{
public:
    explicit buffer_error(const char* message) :
        std::domain_error(message)
    {
    }

    explicit buffer_error(const std::string& message) :
        std::domain_error(message)
    {
    }
};

template<typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::size_t capacity) :
        buffer_(capacity),
        capacity_(capacity),
        head_(static_cast<std::size_t>(0U)),
        tail_(static_cast<std::size_t>(0U)),
        full_(false)
    {
        if(capacity_ == 0U)
        {
            throw std::domain_error("Buffer capacity must be greater than 0");
        }
    }

    void clear() noexcept
    {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        full_ = false;
    }

    bool is_empty() const noexcept
    {
        return ((full_ == false) && (head_ == tail_));
    }

    bool is_full() const noexcept
    {
        return (full_);
    }

    void write(const T& value)
    {
        if(is_full())
        {
            throw std::domain_error("Buffer is full");
        }
        buffer_[head_] = value;
        advance_head();
    }

    void overwrite(const T& value)
    {
        if(is_full())
        {
            buffer_[head_] = value;
            advance_head();
            tail_ = head_;
        }
        else
        {
            write(value);
        }
    }

    T read()
    {
        if(is_empty())
        {
            throw std::domain_error("Buffer is empty");
        }
        const T value = buffer_[tail_];
        advance_tail();
        return value;
    }

private:
    void advance_head() noexcept
    {
        head_ = (head_ + static_cast<std::size_t>(1U)) % capacity_;
        if(head_ == tail_)
        {
            full_ = true;
        }
    }

    void advance_tail() noexcept
    {
        full_ = false;
        tail_ = (tail_ + static_cast<std::size_t>(1U)) % capacity_;
    }

    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    bool full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
