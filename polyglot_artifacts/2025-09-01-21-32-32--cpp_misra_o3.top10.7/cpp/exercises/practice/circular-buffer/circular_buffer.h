#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/*
 * Generic fixed-capacity circular buffer complying with MISRA C++ rules.
 * - Uses std::size_t for indices (platform-appropriate unsigned type).
 * - Stores elements of client-supplied type T.
 * - All operations execute in constant time.
 */
template <typename T>
class circular_buffer
{
public:
    /* Construct a buffer with the given positive capacity. */
    explicit circular_buffer(std::size_t capacity) :
        m_capacity{capacity},
        m_data(capacity),
        m_head(static_cast<std::size_t>(0U)),
        m_tail(static_cast<std::size_t>(0U)),
        m_full(false)
    {
        if (capacity == static_cast<std::size_t>(0U))
        {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    /* Write a value if space is available; otherwise throw. */
    void write(const T& value)
    {
        if (full())
        {
            throw std::domain_error("Buffer full");
        }

        m_data[m_tail] = value;
        advance(m_tail);

        if (m_tail == m_head)
        {
            m_full = true;
        }
    }

    /* Overwrite the oldest element when the buffer is full. */
    void overwrite(const T& value)
    {
        if (full())
        {
            /* Store the new element at the logical tail position, then move
             * both the head and tail forward so the buffer length remains
             * constant while the oldest element is discarded.
             */
            m_data[m_tail] = value;
            advance(m_head);
            advance(m_tail);
            /* m_full remains true because capacity is unchanged. */
        }
        else
        {
            write(value);
        }
    }

    /* Read and remove the oldest element; throw if the buffer is empty. */
    T read()
    {
        if (empty())
        {
            throw std::domain_error("Buffer empty");
        }

        T value = m_data[m_head];
        advance(m_head);
        m_full = false;

        return value;
    }

    /* Remove all elements without changing the capacity. */
    void clear() noexcept
    {
        m_head = m_tail;
        m_full = false;
    }

    /* Query helpers. */
    [[nodiscard]] bool empty() const noexcept
    {
        return ((!m_full) && (m_head == m_tail));
    }

    [[nodiscard]] bool full() const noexcept
    {
        return m_full;
    }

private:
    void advance(std::size_t& index) noexcept
    {
        /* Cast literal to std::size_t to avoid implicit promotion. */
        index = ((index + static_cast<std::size_t>(1U)) % m_capacity);
    }

    std::size_t    m_capacity;
    std::vector<T> m_data;
    std::size_t    m_head;  /* points to oldest element */
    std::size_t    m_tail;  /* points to next insertion slot */
    bool           m_full;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
