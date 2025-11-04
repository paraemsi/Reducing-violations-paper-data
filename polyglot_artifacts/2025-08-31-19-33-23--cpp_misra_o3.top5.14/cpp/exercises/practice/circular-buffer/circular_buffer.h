#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <string>      /* required for buffers of std::string */

namespace circular_buffer
{

/*
 * Fixed-width unsigned integer type used for all indices and counters to
 * comply with MISRA C++ “no plain unsigned int” rule.
 */
using index_t = std::uint32_t;

/*
 * Generic circular (ring) buffer.
 *
 * The implementation follows the behaviour described in the specification:
 *  • write()      – inserts an element; throws if the buffer is already full.
 *  • overwrite()  – inserts, replacing the oldest element when the buffer
 *                   is full.
 *  • read()       – removes and returns the oldest element; throws if empty.
 *  • clear()      – empties the buffer.
 *
 * All operations are O(1).
 */
template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(index_t capacity) :
        buffer_(),
        capacity_(capacity),
        head_(static_cast<index_t>(0U)),
        tail_(static_cast<index_t>(0U)),
        count_(static_cast<index_t>(0U))
    {
        if (capacity_ == static_cast<index_t>(0U))
        {
            throw std::domain_error("capacity must be greater than zero");
        }

        buffer_.resize(
            static_cast<typename std::vector<T>::size_type>(capacity_));
    }

    void write(const T& value)
    {
        if (is_full())
        {
            throw std::domain_error("buffer is full");
        }

        buffer_[tail_] = value;
        tail_          = next_index(tail_);
        ++count_;
    }

    void overwrite(const T& value)
    {
        if (is_full())
        {
            /* Buffer full: replace the oldest element in-place. */
            buffer_[head_] = value;
            head_          = next_index(head_);
            tail_          = head_;            /* maintain “next write” index   */
            /* count_ remains unchanged (buffer stays full)                    */
        }
        else
        {
            write(value);
        }
    }

    T read()
    {
        if (is_empty())
        {
            throw std::domain_error("buffer is empty");
        }

        T value = buffer_[head_];
        head_   = next_index(head_);
        --count_;
        return value;
    }

    void clear() noexcept
    {
        head_  = static_cast<index_t>(0U);
        tail_  = static_cast<index_t>(0U);
        count_ = static_cast<index_t>(0U);
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (count_ == static_cast<index_t>(0U));
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return (count_ == capacity_);
    }

private:
    [[nodiscard]] index_t next_index(index_t current) const noexcept
    {
        return ((current + static_cast<index_t>(1U)) == capacity_)
                   ? static_cast<index_t>(0U)
                   : static_cast<index_t>(current + static_cast<index_t>(1U));
    }

    std::vector<T> buffer_;
    index_t        capacity_;
    index_t        head_;
    index_t        tail_;
    index_t        count_;
};

}   // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
