#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>     // for std::size_t
#include <cstdint>     // for fixed-width integers
#include <stdexcept>   // for std::overflow_error, std::underflow_error
#include <vector>      // for std::vector

namespace circular_buffer {

/**
 * @brief Fixed-capacity circular (ring) buffer for 32-bit signed integers.
 *
 * The buffer starts empty and throws std::underflow_error on read()
 * when empty.  A write() to a full buffer throws std::overflow_error.
 * overwrite() always succeeds by discarding the oldest element first
 * when the buffer is already full.
 */
/**
 * @brief Fixed-capacity circular (ring) buffer.
 *
 * Template is header-only so that any value_type can be used without the
 * need for explicit instantiation.
 */
template <typename T>
class circular_buffer
{
public:
    using value_type = T;

    explicit circular_buffer(std::size_t capacity)
        : m_storage(capacity)
    {
        /* nothing further to do */
    }

    void clear() noexcept
    {
        m_head = static_cast<std::size_t>(0);
        m_tail = static_cast<std::size_t>(0);
        m_full = false;
    }

    void write(const value_type& value)
    {
        if (full())
        {
            throw std::domain_error("circular buffer is full");
        }

        m_storage[m_tail] = value;
        m_tail = (m_tail + static_cast<std::size_t>(1)) % m_storage.size();

        if (m_tail == m_head)
        {
            m_full = true;
        }
    }

    void overwrite(const value_type& value)
    {
        if (full())
        {
            /* discard the oldest element first */
            m_storage[m_head] = value;
            m_head = (m_head + static_cast<std::size_t>(1)) % m_storage.size();
            m_tail = (m_tail + static_cast<std::size_t>(1)) % m_storage.size();
        }
        else
        {
            write(value);
        }
    }

    [[nodiscard]] value_type read()
    {
        if (empty())
        {
            throw std::domain_error("circular buffer is empty");
        }

        value_type result = m_storage[m_head];
        m_head = (m_head + static_cast<std::size_t>(1)) % m_storage.size();
        m_full = false;

        return result;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return (!m_full) && (m_head == m_tail);
    }

    [[nodiscard]] bool full() const noexcept
    {
        return m_full;
    }

    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return m_storage.size();
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        if (m_full)
        {
            return m_storage.size();
        }

        if (m_tail >= m_head)
        {
            return m_tail - m_head;
        }

        return (m_storage.size() - m_head) + m_tail;
    }

private:
    std::vector<value_type> m_storage;   /* internal data buffer              */
    std::size_t             m_head{0U};  /* index of next element to read     */
    std::size_t             m_tail{0U};  /* index of next element to write    */
    bool                    m_full{false}; /* true when buffer completely full */
};

}   // namespace circular_buffer

#endif /* CIRCULAR_BUFFER_H */
