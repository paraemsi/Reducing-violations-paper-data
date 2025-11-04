#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

using index_t = std::uint32_t;

/* Custom exception types required by the exercise */
struct buffer_empty final : public std::domain_error
{
    buffer_empty() : std::domain_error("empty buffer") {}
};

struct buffer_full final : public std::domain_error
{
    buffer_full() : std::domain_error("full buffer") {}
};

template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(index_t capacity);

    void write(const T& value);
    T read();
    void clear();
    void overwrite(const T& value);

    [[nodiscard]] bool is_empty() const noexcept;
    [[nodiscard]] bool is_full() const noexcept;

private:
    std::vector<T> m_buffer;
    index_t m_capacity;
    index_t m_head;
    index_t m_tail;
    index_t m_count;
};

template <typename T>
inline circular_buffer<T>::circular_buffer(const index_t capacity)
    : m_buffer(static_cast<std::size_t>(capacity)),
      m_capacity(capacity),
      m_head(0U),
      m_tail(0U),
      m_count(0U)
{
    if (capacity == 0U)
    {
        throw std::invalid_argument("capacity must be > 0");
    }
}

template <typename T>
inline void circular_buffer<T>::write(const T& value)
{
    if (is_full())
    {
        throw buffer_full();
    }

    m_buffer[static_cast<std::size_t>(m_tail)] = value;
    m_tail = ((m_tail + static_cast<index_t>(1U)) % m_capacity);
    ++m_count;
}

template <typename T>
inline T circular_buffer<T>::read()
{
    if (is_empty())
    {
        throw buffer_empty();
    }

    T value = m_buffer[static_cast<std::size_t>(m_head)];
    m_head = ((m_head + static_cast<index_t>(1U)) % m_capacity);
    --m_count;
    return value;
}

template <typename T>
inline void circular_buffer<T>::clear()
{
    m_head = 0U;
    m_tail = 0U;
    m_count = 0U;
}

template <typename T>
inline void circular_buffer<T>::overwrite(const T& value)
{
    if (is_full())
    {
        /* Discard the oldest element before writing the new one */
        m_head = ((m_head + static_cast<index_t>(1U)) % m_capacity);
        --m_count;
    }

    write(value);
}

template <typename T>
inline bool circular_buffer<T>::is_empty() const noexcept
{
    return (m_count == 0U);
}

template <typename T>
inline bool circular_buffer<T>::is_full() const noexcept
{
    return (m_count == m_capacity);
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
