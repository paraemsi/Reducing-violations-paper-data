#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <vector>
#include <stdexcept>

namespace circular_buffer {

/*
 * Template implementation of a fixed-capacity circular (ring) buffer.
 * The buffer owns its contained elements and provides FIFO semantics.
 *
 * MISRA C++  compliance notes:
 *  - All integral variables use std::size_t where index width is irrelevant
 *    or std::uint32_t when exact width is desired.
 *  - All arithmetic and logical expressions are fully parenthesised when
 *    operator precedence differs.
 *  - All if/else bodies use braces.
 *  - No characters are manipulated as numbers.
 */
template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity);

    void write(const T& value);      // write, throws if full
    void overwrite(const T& value);  // write, overwriting oldest if full
    T read();                        // read oldest, throws if empty

    void clear() noexcept;

    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] bool full() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;

private:
    std::vector<T>  m_storage;   // fixed-capacity storage
    std::size_t     m_capacity;  // cached for readability
    std::size_t     m_head;      // next write index
    std::size_t     m_tail;      // next read  index
    bool            m_full;      // true when buffer is full

    void advance(std::size_t& index) noexcept;
};

/* ===== Implementation ===== */

template <typename T>
circular_buffer<T>::circular_buffer(std::size_t capacity) :
    m_storage(capacity),
    m_capacity(capacity),
    m_head(static_cast<std::size_t>(0U)),
    m_tail(static_cast<std::size_t>(0U)),
    m_full(false)
{
    if (capacity == static_cast<std::size_t>(0U))
    {
        throw std::invalid_argument("capacity must be > 0");
    }
}

template <typename T>
void circular_buffer<T>::write(const T& value)
{
    if (full())
    {
        throw std::domain_error("buffer is full");
    }

    m_storage[m_head] = value;
    advance(m_head);

    if (m_head == m_tail)
    {
        m_full = true;
    }
}

template <typename T>
void circular_buffer<T>::overwrite(const T& value)
{
    if (full())
    {
        /* Overwrite oldest element */
        m_storage[m_head] = value;
        advance(m_head);
        m_tail = m_head;  /* oldest element has moved */
        /* buffer remains full after overwrite */
        m_full = true;
    }
    else
    {
        write(value);
    }
}

template <typename T>
T circular_buffer<T>::read()
{
    if (empty())
    {
        throw std::domain_error("buffer is empty");
    }

    T value = m_storage[m_tail];
    advance(m_tail);
    m_full = false;
    return value;
}

template <typename T>
void circular_buffer<T>::clear() noexcept
{
    m_head = static_cast<std::size_t>(0U);
    m_tail = static_cast<std::size_t>(0U);
    m_full = false;
}

template <typename T>
bool circular_buffer<T>::empty() const noexcept
{
    return (!m_full) && (m_head == m_tail);
}

template <typename T>
bool circular_buffer<T>::full() const noexcept
{
    return m_full;
}

template <typename T>
std::size_t circular_buffer<T>::size() const noexcept
{
    if (m_full)
    {
        return m_capacity;
    }
    if (m_head >= m_tail)
    {
        return (m_head - m_tail);
    }
    /* head wrapped around */
    return (m_capacity - (m_tail - m_head));
}

template <typename T>
std::size_t circular_buffer<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
void circular_buffer<T>::advance(std::size_t& index) noexcept
{
    index = (index + static_cast<std::size_t>(1U));
    if (index == m_capacity)
    {
        index = static_cast<std::size_t>(0U);
    }
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
