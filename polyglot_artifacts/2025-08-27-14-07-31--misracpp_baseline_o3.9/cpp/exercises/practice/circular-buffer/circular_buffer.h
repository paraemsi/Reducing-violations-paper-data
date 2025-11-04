#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace circular_buffer {

template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity)
        : m_buffer(capacity),
          m_head(0),
          m_tail(0),
          m_capacity(capacity),
          m_full(false)
    {
        if (capacity == 0)
        {
            throw std::invalid_argument("Buffer capacity must be > 0");
        }
    }

    void clear()
    {
        m_head = m_tail;
        m_full = false;
    }

    void write(T value)
    {
        if (full())
        {
            throw std::domain_error("Buffer is full");
        }

        m_buffer[m_tail] = std::move(value);
        advance_tail();
    }

    void overwrite(T value)
    {
        if (full())
        {
            // Overwrite the oldest element (pointed to by m_head) and keep the
            // buffer in a full state.
            m_buffer[m_head] = std::move(value);
            advance_head();       // drop the overwritten element
            m_tail = m_head;      // tail follows head when the buffer is full
            m_full = true;        // restore full flag
        }
        else
        {
            write(std::move(value));
        }
    }

    T read()
    {
        if (empty())
        {
            throw std::domain_error("Buffer is empty");
        }

        T value = std::move(m_buffer[m_head]);
        advance_head();
        return value;
    }

    bool empty() const noexcept
    {
        return (!m_full && (m_head == m_tail));
    }

    bool full() const noexcept
    {
        return m_full;
    }

    std::size_t capacity() const noexcept
    {
        return m_capacity;
    }

    std::size_t size() const noexcept
    {
        if (m_full)
        {
            return m_capacity;
        }
        if (m_tail >= m_head)
        {
            return m_tail - m_head;
        }
        return m_capacity + m_tail - m_head;
    }

private:
    void advance_head()
    {
        m_head = (m_head + 1) % m_capacity;
        m_full = false;
    }

    void advance_tail()
    {
        m_tail = (m_tail + 1) % m_capacity;
        if (m_tail == m_head)
        {
            m_full = true;
        }
    }

    std::vector<T> m_buffer;
    std::size_t    m_head;
    std::size_t    m_tail;
    std::size_t    m_capacity;
    bool           m_full;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
