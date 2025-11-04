#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

// Exception raised when attempting to write to a full buffer
class buffer_full_error final : public std::runtime_error
{
public:
    buffer_full_error() : std::runtime_error("circular buffer is full") {}
};


// Exception raised when attempting to read from an empty buffer
class buffer_empty_error final : public std::runtime_error
{
public:
    buffer_empty_error() : std::runtime_error("circular buffer is empty") {}
};

template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity);

    circular_buffer(const circular_buffer&) = default;
    circular_buffer(circular_buffer&&) noexcept = default;
    circular_buffer& operator=(const circular_buffer&) = default;
    circular_buffer& operator=(circular_buffer&&) noexcept = default;
    ~circular_buffer() = default;

    void write(const T& item);
    void overwrite(const T& item);
    T read();
    void clear() noexcept;

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;

private:
    std::vector<T> m_storage;
    std::size_t m_capacity {0U};
    std::size_t m_head {0U}; // next position to write
    std::size_t m_tail {0U}; // next position to read
    bool m_full {false};

    [[nodiscard]] std::size_t advance(std::size_t index) const noexcept;
};

// --- CircularBuffer inline definitions ---
template <typename T>
inline circular_buffer<T>::circular_buffer(std::size_t capacity)
    : m_storage(capacity),
      m_capacity(capacity),
      m_head(0U),
      m_tail(0U),
      m_full(false)
{
    /* no further initialisation required */
}

template <typename T>
inline void circular_buffer<T>::write(const T& item)
{
    if (m_full)
    {
        throw std::domain_error("circular buffer is full");
    }

    m_storage[m_head] = item;
    m_head = advance(m_head);

    if (m_head == m_tail)
    {
        m_full = true;
    }
}

template <typename T>
inline void circular_buffer<T>::overwrite(const T& item)
{
    if (m_full)
    {
        m_storage[m_head] = item;
        m_head = advance(m_head);
        m_tail = m_head; /* oldest element overwritten */
    }
    else
    {
        write(item);
    }
}

template <typename T>
inline T circular_buffer<T>::read()
{
    if ((!m_full) && (m_head == m_tail))
    {
        throw std::domain_error("circular buffer is empty");
    }

    T value {m_storage[m_tail]};
    m_tail = advance(m_tail);
    m_full = false;
    return value;
}

template <typename T>
inline void circular_buffer<T>::clear() noexcept
{
    m_head = 0U;
    m_tail = 0U;
    m_full = false;
}

template <typename T>
inline std::size_t circular_buffer<T>::size() const noexcept
{
    if (m_full)
    {
        return m_capacity;
    }

    if (m_head >= m_tail)
    {
        return (m_head - m_tail);
    }

    return (m_capacity + m_head - m_tail);
}

template <typename T>
inline std::size_t circular_buffer<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
inline std::size_t circular_buffer<T>::advance(std::size_t index) const noexcept
{
    ++index;
    if (index >= m_capacity)
    {
        index = 0U;
    }
    return index;
}

} // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
