#include "circular_buffer.h"

#if 0   /* implementation moved to header – file kept for build systems */

namespace circular_buffer {

CircularBuffer::CircularBuffer(std::size_t capacity)
    : m_storage(capacity)
{
    /* no further initialisation required */
}

void CircularBuffer::clear() noexcept
{
    m_head = 0U;
    m_tail = 0U;
    m_full = false;
}

void CircularBuffer::write(const value_type value)
{
    if (full())
    {
        throw std::overflow_error("circular buffer is full");
    }

    m_storage[m_tail] = value;
    m_tail = (m_tail + static_cast<std::size_t>(1)) % m_storage.size();

    if (m_tail == m_head)
    {
        m_full = true;
    }
}

void CircularBuffer::overwrite(const value_type value)
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

CircularBuffer::value_type CircularBuffer::read()
{
    if (empty())
    {
        throw std::underflow_error("circular buffer is empty");
    }

    const value_type result = m_storage[m_head];
    m_head = (m_head + static_cast<std::size_t>(1)) % m_storage.size();
    m_full = false;

    return result;
}

bool CircularBuffer::empty() const noexcept
{
    return (!m_full) && (m_head == m_tail);
}

bool CircularBuffer::full() const noexcept
{
    return m_full;
}

std::size_t CircularBuffer::capacity() const noexcept
{
    return m_storage.size();
}

std::size_t CircularBuffer::size() const noexcept
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

}   // namespace circular_buffer
#endif /* TEMPLATE_IMPLEMENTATION_DISABLED */
