#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/*
 * Generic fixed-capacity circular buffer that satisfies the basic
 * requirements of the Exercism exercise while adhering to the
 * provided MISRA C++ subset.
 */
template <typename T>
class CircularBuffer final
{
public:
    explicit CircularBuffer(std::uint32_t capacity);

    void write(const T& value);
    void overwrite(const T& value);
    T    read();
    void clear() noexcept;

private:
    std::vector<T> data_;
    std::uint32_t  capacity_;
    std::uint32_t  head_;
    std::uint32_t  tail_;
    std::uint32_t  size_;

    std::uint32_t next_index(std::uint32_t index) const noexcept;
};

/* provide template alias expected by the test suite */
template <typename T>
using circular_buffer = CircularBuffer<T>;

/* ==== Implementation (header-only to keep templates linkable) ==== */

template <typename T>
CircularBuffer<T>::CircularBuffer(std::uint32_t capacity) :
    data_(static_cast<std::size_t>(capacity)),
    capacity_(capacity),
    head_(static_cast<std::uint32_t>(0U)),
    tail_(static_cast<std::uint32_t>(0U)),
    size_(static_cast<std::uint32_t>(0U))
{
    if (capacity_ == static_cast<std::uint32_t>(0U))
    {
        throw std::invalid_argument("Capacity must be greater than zero");
    }
}

template <typename T>
void CircularBuffer<T>::write(const T& value)
{
    if (size_ == capacity_)
    {
        throw std::domain_error("Circular buffer is full");
    }

    data_[static_cast<std::size_t>(head_)] = value;
    head_ = next_index(head_);
    size_ = static_cast<std::uint32_t>(size_ + static_cast<std::uint32_t>(1U));
}

template <typename T>
void CircularBuffer<T>::overwrite(const T& value)
{
    if (size_ == capacity_)
    {
        /* buffer full: replace oldest element at tail, advance tail and head */
        data_[static_cast<std::size_t>(tail_)] = value;
        tail_ = next_index(tail_);
        head_ = tail_;
    }
    else
    {
        write(value);
    }
}

template <typename T>
T CircularBuffer<T>::read()
{
    if (size_ == static_cast<std::uint32_t>(0U))
    {
        throw std::domain_error("Circular buffer is empty");
    }

    T value = data_[static_cast<std::size_t>(tail_)];
    tail_ = next_index(tail_);
    size_ = static_cast<std::uint32_t>(size_ - static_cast<std::uint32_t>(1U));
    return value;
}

template <typename T>
void CircularBuffer<T>::clear() noexcept
{
    head_ = static_cast<std::uint32_t>(0U);
    tail_ = static_cast<std::uint32_t>(0U);
    size_ = static_cast<std::uint32_t>(0U);
}

template <typename T>
std::uint32_t CircularBuffer<T>::next_index(std::uint32_t index) const noexcept
{
    return ((index + static_cast<std::uint32_t>(1U)) % capacity_);
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
