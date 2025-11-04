#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class CircularBuffer
{
public:
    explicit CircularBuffer(std::uint32_t capacity) :
        m_capacity(capacity),
        m_data(capacity),
        m_head(0U),
        m_tail(0U),
        m_size(0U)
    {
        if (capacity == 0U)
        {
            throw std::domain_error("capacity must be greater than zero");
        }
    }

    void clear() noexcept
    {
        m_head = 0U;
        m_tail = 0U;
        m_size = 0U;
    }

    void write(const T& item)
    {
        if (m_size == m_capacity)
        {
            throw std::domain_error("buffer is full");
        }

        m_data[m_tail] = item;
        m_tail = advance(m_tail);
        ++m_size;
    }

    void overwrite(const T& item)
    {
        if (m_size == m_capacity)
        {
            m_data[m_tail] = item;
            m_tail = advance(m_tail);
            m_head = m_tail;
        }
        else
        {
            write(item);
        }
    }

    T read()
    {
        if (m_size == 0U)
        {
            throw std::domain_error("buffer is empty");
        }

        T value = m_data[m_head];
        m_head = advance(m_head);
        --m_size;
        return value;
    }

private:
    [[nodiscard]] std::uint32_t advance(std::uint32_t index) const noexcept
    {
        return ((index + 1U) % m_capacity);
    }

    std::uint32_t   m_capacity;
    std::vector<T>  m_data;
    std::uint32_t   m_head;
    std::uint32_t   m_tail;
    std::uint32_t   m_size;
};

template <typename T>
using circular_buffer = CircularBuffer<T>;

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
