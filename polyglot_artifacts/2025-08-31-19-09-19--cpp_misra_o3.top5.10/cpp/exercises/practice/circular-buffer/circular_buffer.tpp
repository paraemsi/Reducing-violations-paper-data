#pragma once
#include <utility>

namespace circular_buffer {

template <typename T>
CircularBuffer<T>::CircularBuffer(std::size_t capacity)
    : m_storage(capacity),
      m_capacity(capacity),
      m_head(0U),
      m_tail(0U),
      m_size(0U)
{
    if(capacity == 0U)
    {
        throw std::invalid_argument("capacity must be > 0");
    }
}

template <typename T>
void CircularBuffer<T>::write(const T& value)
{
    if(full())
    {
        throw std::domain_error("buffer full");
    }

    m_storage[m_head] = value;
    m_head = ((m_head + 1U) % m_capacity);
    ++m_size;
}

template <typename T>
void CircularBuffer<T>::overwrite(const T& value)
{
    if(full())
    {
        /* overwrite at current head position, then advance both head and tail */
        m_storage[m_head] = value;
        m_head = ((m_head + 1U) % m_capacity);
        m_tail = m_head;
        /* m_size remains unchanged (buffer stays full) */
    }
    else
    {
        write(value);
    }
}

template <typename T>
T CircularBuffer<T>::read()
{
    if(empty())
    {
        throw std::domain_error("buffer empty");
    }

    T value = m_storage[m_tail];
    m_tail = ((m_tail + 1U) % m_capacity);
    --m_size;
    return value;
}

template <typename T>
void CircularBuffer<T>::clear()
{
    m_head = 0U;
    m_tail = 0U;
    m_size = 0U;
}

template <typename T>
bool CircularBuffer<T>::empty() const noexcept
{
    return (m_size == 0U);
}

template <typename T>
bool CircularBuffer<T>::full() const noexcept
{
    return (m_size == m_capacity);
}

} // namespace circular_buffer
