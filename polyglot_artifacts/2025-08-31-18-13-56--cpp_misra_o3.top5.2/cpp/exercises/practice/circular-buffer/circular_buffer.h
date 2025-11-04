#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>      // for std::size_t
#include <cstdint>      // fixed-width integer types (MISRA compliance)
#include <stdexcept>    // for std::runtime_error
#include <vector>       // storage container
#include <string>       // required for std::string instantiations used by tests

namespace circular_buffer {

/*
 * A fixed-capacity circular (ring) buffer.
 * T must be copy-assignable and default-constructible.
 */
template <typename T>
class CircularBuffer
{
public:
    explicit CircularBuffer(std::size_t capacity) :
        buffer_(capacity),
        head_(0U),
        tail_(0U),
        full_(false)
    {
        if (capacity == 0U) {
            throw std::invalid_argument("capacity must be greater than zero");
        }
    }

    void clear() noexcept
    {
        head_ = 0U;
        tail_ = 0U;
        full_ = false;
    }

    void write(const T& item)
    {
        if (is_full()) {
            throw std::domain_error("circular buffer is full");
        }

        buffer_[head_] = item;
        advance_head();

        if (head_ == tail_) {
            full_ = true;
        }
    }

    T read()
    {
        if (is_empty()) {
            throw std::domain_error("circular buffer is empty");
        }

        T item = buffer_[tail_];
        advance_tail();
        full_ = false;
        return item;
    }

    void overwrite(const T& item)
    {
        if (is_full()) {
            buffer_[head_] = item;
            advance_head();
            tail_ = head_;
        } else {
            write(item);
        }
        full_ = (head_ == tail_);
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (!full_) && (head_ == tail_);
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return full_;
    }

    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return buffer_.size();
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        if (full_) {
            return buffer_.size();
        }

        if (head_ >= tail_) {
            return head_ - tail_;
        }

        return buffer_.size() - (tail_ - head_);
    }

private:
    std::vector<T> buffer_;
    std::size_t    head_;
    std::size_t    tail_;
    bool           full_;

    void advance_head() noexcept
    {
        if ((head_ + 1U) >= buffer_.size()) {
            head_ = 0U;
        } else {
            ++head_;
        }
    }

    void advance_tail() noexcept
    {
        if ((tail_ + 1U) >= buffer_.size()) {
            tail_ = 0U;
        } else {
            ++tail_;
        }
    }
};

/*
 * Wrapper class required by the exercise tests so that the type
 * name matches the namespace:
 *     circular_buffer::circular_buffer<T> buffer(capacity);
 *
 * It simply inherits all functionality from CircularBuffer<T>.
 */
template <typename T>
class circular_buffer final : public CircularBuffer<T>
{
public:
    explicit circular_buffer(std::size_t capacity) : CircularBuffer<T>(capacity)
    {
        /* delegate construction to base class */
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
