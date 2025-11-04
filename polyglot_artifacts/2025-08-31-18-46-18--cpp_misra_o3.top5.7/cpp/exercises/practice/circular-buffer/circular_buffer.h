#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/*
 * Generic fixed-capacity circular (ring) buffer.
 * All operations are O(1) with a fixed capacity (amortized constant time).
 */
template <typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::size_t capacity);

    void clear() noexcept;
    void write(const T& item);
    void overwrite(const T& item);
    T    read();

    [[nodiscard]] bool is_empty() const noexcept;
    [[nodiscard]] bool is_full()  const noexcept;

private:
    std::vector<T> buffer_;
    std::size_t    capacity_;
    std::size_t    head_;
    std::size_t    tail_;
    bool           full_;

    void advance(std::size_t& index) noexcept;
};

/* ---------- implementation ---------- */

template <typename T>
circular_buffer<T>::circular_buffer(const std::size_t capacity) :
    buffer_(capacity),
    capacity_(capacity),
    head_(static_cast<std::size_t>(0U)),
    tail_(static_cast<std::size_t>(0U)),
    full_(false)
{
    if (capacity == static_cast<std::size_t>(0U))
    {
        throw std::invalid_argument("capacity must be greater than 0");
    }
}

template <typename T>
void circular_buffer<T>::clear() noexcept
{
    head_ = tail_;
    full_ = false;
}

template <typename T>
void circular_buffer<T>::write(const T& item)
{
    if (full_)
    {
        throw std::domain_error("buffer full");
    }

    buffer_[tail_] = item;
    advance(tail_);

    if (tail_ == head_)
    {
        full_ = true;
    }
}

template <typename T>
void circular_buffer<T>::overwrite(const T& item)
{
    if (full_)
    {
        buffer_[tail_] = item;
        advance(tail_);
        head_ = tail_;
    }
    else
    {
        write(item);
    }
}

template <typename T>
T circular_buffer<T>::read()
{
    if ((!full_) && (head_ == tail_))
    {
        throw std::domain_error("buffer empty");
    }

    const T value = buffer_[head_];
    advance(head_);
    full_ = false;
    return value;
}

template <typename T>
bool circular_buffer<T>::is_empty() const noexcept
{
    return ((!full_) && (head_ == tail_));
}

template <typename T>
bool circular_buffer<T>::is_full() const noexcept
{
    return full_;
}

template <typename T>
void circular_buffer<T>::advance(std::size_t& index) noexcept
{
    index = index + static_cast<std::size_t>(1U);
    if (index == capacity_)
    {
        index = static_cast<std::size_t>(0U);
    }
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
