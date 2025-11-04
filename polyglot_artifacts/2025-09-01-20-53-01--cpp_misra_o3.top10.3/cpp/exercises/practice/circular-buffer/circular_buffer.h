#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/**
 * \brief Fixed-capacity circular (ring) buffer that supports
 *        write, overwrite and read operations.
 *
 * \tparam T Element type stored in the buffer.
 */
template<typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::uint32_t capacity);

    void clear() noexcept;

    [[nodiscard]] bool is_empty() const noexcept;
    [[nodiscard]] bool is_full() const noexcept;

    void write(const T & item);
    void overwrite(const T & item);
    [[nodiscard]] T read();

    [[nodiscard]] std::uint32_t size() const noexcept;
    [[nodiscard]] std::uint32_t capacity() const noexcept;

private:
    std::vector<T> buffer_;
    std::uint32_t head_{std::uint32_t{0}};      // index of next write
    std::uint32_t tail_{std::uint32_t{0}};      // index of next read
    const std::uint32_t max_capacity_;  // total storage slots
    std::uint32_t count_{std::uint32_t{0}};     // number of elements currently stored
};

/* -------------------------------------------------------------------------- */
/*                              Implementation                                */
/* -------------------------------------------------------------------------- */

template<typename T>
circular_buffer<T>::circular_buffer(std::uint32_t capacity) :
    buffer_(capacity),
    max_capacity_(capacity)
{
    if(capacity == std::uint32_t{0})
    {
        throw std::domain_error("capacity must be > 0");
    }
}

template<typename T>
void circular_buffer<T>::clear() noexcept
{
    head_  = std::uint32_t{0};
    tail_  = std::uint32_t{0};
    count_ = std::uint32_t{0};
}

template<typename T>
bool circular_buffer<T>::is_empty() const noexcept
{
    return (count_ == std::uint32_t{0});
}

template<typename T>
bool circular_buffer<T>::is_full() const noexcept
{
    return (count_ == max_capacity_);
}

template<typename T>
void circular_buffer<T>::write(const T & item)
{
    if(is_full())
    {
        throw std::domain_error("buffer is full");
    }

    buffer_[head_] = item;
    head_          = (head_ + std::uint32_t{1}) % max_capacity_;
    ++count_;
}

template<typename T>
void circular_buffer<T>::overwrite(const T & item)
{
    if(is_full())
    {
        buffer_[head_] = item;
        head_          = (head_ + std::uint32_t{1}) % max_capacity_;
        tail_          = head_; /* oldest element overwritten */
    }
    else
    {
        write(item);
    }
}

template<typename T>
T circular_buffer<T>::read()
{
    if(is_empty())
    {
        throw std::domain_error("buffer is empty");
    }

    T value = buffer_[tail_];
    tail_   = (tail_ + std::uint32_t{1}) % max_capacity_;
    --count_;
    return value;
}

template<typename T>
std::uint32_t circular_buffer<T>::size() const noexcept
{
    return count_;
}

template<typename T>
std::uint32_t circular_buffer<T>::capacity() const noexcept
{
    return max_capacity_;
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
