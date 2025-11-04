#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

/*  Generic circular buffer -------------------------------------------------
 *  Fixed-capacity, exception-safe queue that preserves elements in FIFO
 *  order.  Overwrite semantics replace the oldest element when the buffer is
 *  already full.
 */
template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::uint32_t capacity);

    void write(const T& value);
    void overwrite(const T& value);
    T read();
    void clear() noexcept;

    std::uint32_t size() const noexcept;
    std::uint32_t capacity() const noexcept;

private:
    std::uint32_t advance(std::uint32_t index) const noexcept;

    std::uint32_t m_capacity;        /* total slots                       */
    std::uint32_t m_head;            /* next element to read              */
    std::uint32_t m_tail;            /* next slot to write                */
    std::uint32_t m_count;           /* number of stored elements         */
    std::vector<T> m_storage;        /* underlying container              */
};


/* ===== Implementation =================================================== */

template <typename T>
circular_buffer<T>::circular_buffer(std::uint32_t capacity)
    : m_capacity(capacity),
      m_head(0U),
      m_tail(0U),
      m_count(0U),
      m_storage(capacity)
{
    if (capacity == 0U) {
        throw std::invalid_argument("Capacity must be greater than 0");
    }
}

template <typename T>
void circular_buffer<T>::write(const T& value)
{
    if (m_count == m_capacity) {
        throw std::domain_error("Buffer full");
    } else {
        m_storage[m_tail] = value;
        m_tail = advance(m_tail);
        m_count = static_cast<std::uint32_t>(m_count + static_cast<std::uint32_t>(1U));
    }
}

template <typename T>
void circular_buffer<T>::overwrite(const T& value)
{
    if (m_count == m_capacity) {
        m_storage[m_tail] = value;
        m_head = advance(m_head);   /* drop oldest                       */
        m_tail = advance(m_tail);
    } else {
        write(value);
    }
}

template <typename T>
T circular_buffer<T>::read()
{
    if (m_count == 0U) {
        throw std::domain_error("Buffer empty");
    } else {
        T value{std::move(m_storage[m_head])};
        m_head = advance(m_head);
        m_count = static_cast<std::uint32_t>(m_count - static_cast<std::uint32_t>(1U));
        return value;
    }
}

template <typename T>
void circular_buffer<T>::clear() noexcept
{
    m_head  = 0U;
    m_tail  = 0U;
    m_count = 0U;
}

template <typename T>
std::uint32_t circular_buffer<T>::size() const noexcept
{
    return m_count;
}

template <typename T>
std::uint32_t circular_buffer<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
std::uint32_t circular_buffer<T>::advance(std::uint32_t index) const noexcept
{
    /* (index + 1) % m_capacity, parenthesised for explicit precedence       */
    return static_cast<std::uint32_t>(
        ((index + static_cast<std::uint32_t>(1U)) % m_capacity));
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
