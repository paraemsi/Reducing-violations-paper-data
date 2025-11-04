#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/* Exceptions ----------------------------------------------------------------*/
class buffer_empty final : public std::domain_error
{
public:
    explicit buffer_empty() : std::domain_error("Buffer is empty") {}
};

class buffer_full final : public std::domain_error
{
public:
    explicit buffer_full() : std::domain_error("Buffer is full") {}
};

/* Circular buffer -----------------------------------------------------------*/
template <typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::size_t capacity) : m_buffer(capacity), m_capacity(capacity)
    {
        /* A buffer of size 0 makes no sense – prevent undefined behaviour      */
        if (capacity == static_cast<std::size_t>(0U))
        {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    void write(const T& value)
    {
        if (m_size == m_capacity)
        {
            throw buffer_full();
        }

        m_buffer[m_head] = value;
        m_head = (m_head + static_cast<std::size_t>(1U)) % m_capacity;
        ++m_size;
    }

    void overwrite(const T& value)
    {
        if (m_size == m_capacity)
        {
            /* Buffer full: overwrite at the logical write position (m_head)      */
            m_buffer[m_head] = value;
            m_head = (m_head + static_cast<std::size_t>(1U)) % m_capacity;
            m_tail = m_head; /* oldest element has been discarded                 */
        }
        else
        {
            write(value);
        }
    }

    T read()
    {
        if (m_size == static_cast<std::size_t>(0U))
        {
            throw buffer_empty();
        }

        T value{m_buffer[m_tail]};
        m_tail = (m_tail + static_cast<std::size_t>(1U)) % m_capacity;
        --m_size;
        return value;
    }

    void clear() noexcept
    {
        m_head = static_cast<std::size_t>(0U);
        m_tail = static_cast<std::size_t>(0U);
        m_size = static_cast<std::size_t>(0U);
    }

private:
    std::vector<T> m_buffer;
    std::size_t    m_capacity{0U};
    std::size_t    m_head{0U};  /* Next position to write                         */
    std::size_t    m_tail{0U};  /* Next position to read                          */
    std::size_t    m_size{0U};  /* Current number of stored elements              */
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
