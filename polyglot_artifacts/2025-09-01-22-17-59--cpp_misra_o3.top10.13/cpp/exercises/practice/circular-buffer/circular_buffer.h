#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <cstdint>

namespace circular_buffer {

template<typename T>
class circular_buffer {
public:
    using index_type = std::uint32_t;
    explicit circular_buffer(index_type capacity) :
        buffer_(static_cast<std::size_t>(capacity)),
        head_{0U},
        tail_{0U},
        full_{false}
    {
        if(capacity == 0U)
        {
            throw std::invalid_argument("capacity must be > 0");
        }
    }

    void clear() noexcept
    {
        head_ = 0U;
        tail_ = 0U;
        full_ = false;
    }

    bool is_empty() const noexcept
    {
        return (!full_) && (head_ == tail_);
    }

    bool is_full() const noexcept
    {
        return full_;
    }

    T read()
    {
        if(is_empty())
        {
            throw std::domain_error("empty buffer");
        }

        T value = buffer_[tail_];
        tail_ = static_cast<index_type>(
            (static_cast<std::size_t>(tail_) + static_cast<std::size_t>(1U)) %
            buffer_.size());
        full_ = false;
        return value;
    }

    void write(const T& value)
    {
        if(full_)
        {
            throw std::domain_error("full buffer");
        }

        buffer_[head_] = value;
        advance_head();
    }

    void overwrite(const T& value)
    {
        if(full_)
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

private:
    void advance_head()
    {
        head_ = static_cast<index_type>(
            (static_cast<std::size_t>(head_) + static_cast<std::size_t>(1U)) %
            buffer_.size());
        if(head_ == tail_)
        {
            full_ = true;
        }
    }

    std::vector<T> buffer_;
    index_type     head_;
    index_type     tail_;
    bool           full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
