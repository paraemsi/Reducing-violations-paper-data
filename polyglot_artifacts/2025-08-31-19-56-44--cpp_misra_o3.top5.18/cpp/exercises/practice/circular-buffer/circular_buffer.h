#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <cstddef>

namespace circular_buffer {

/*
 * Generic fixed-capacity circular buffer that satisfies the rules requested:
 *  - uses fixed-width integer types (<cstdint>)
 *  - avoids built-in signed/unsigned integral type names
 *  - bodies of if/else are compound statements
 *  - operator precedence is made explicit with parentheses
 */
template <typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::uint32_t capacity) :
        buffer_(static_cast<std::size_t>(capacity)),
        capacity_(capacity),
        head_(0U),
        tail_(0U),
        full_(false)
    {
        if (capacity == 0U) {
            throw std::invalid_argument("capacity must be greater than 0");
        }
    }

    void write(const T& item)
    {
        if (full_) {
            throw std::domain_error("buffer is full");
        }
        buffer_[static_cast<std::size_t>(head_)] = item;
        advance_head();
    }

    void overwrite(const T& item) noexcept
    {
        if (full_) {
            buffer_[static_cast<std::size_t>(head_)] = item;
            advance_head();
            tail_ = head_;
        } else {
            write(item);
        }
    }

    T read()
    {
        if (is_empty()) {
            throw std::domain_error("buffer is empty");
        }

        const T value = buffer_[static_cast<std::size_t>(tail_)];
        advance_tail();
        return value;
    }

    void clear() noexcept
    {
        head_ = 0U;
        tail_ = 0U;
        full_ = false;
    }

    bool is_empty() const noexcept
    {
        return ((full_ == false) && (head_ == tail_));
    }

    bool is_full() const noexcept
    {
        return full_;
    }

    std::uint32_t capacity() const noexcept
    {
        return capacity_;
    }

    std::uint32_t size() const noexcept
    {
        if (full_) {
            return capacity_;
        }

        if (head_ >= tail_) {
            return (head_ - tail_);
        }

        return (capacity_ + head_ - tail_);
    }

private:
    void advance_head() noexcept
    {
        head_ = (head_ + 1U);
        if (head_ >= capacity_) {
            head_ = 0U;
        }

        if (head_ == tail_) {
            full_ = true;
        }
    }

    void advance_tail() noexcept
    {
        full_ = false;
        tail_ = (tail_ + 1U);
        if (tail_ >= capacity_) {
            tail_ = 0U;
        }
    }

    std::vector<T> buffer_;
    std::uint32_t   capacity_;
    std::uint32_t   head_;
    std::uint32_t   tail_;
    bool            full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
