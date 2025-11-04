#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity) :
        m_capacity(capacity),
        m_data(capacity),
        m_head(static_cast<std::size_t>(0)),
        m_tail(static_cast<std::size_t>(0)),
        m_size(static_cast<std::size_t>(0))
    {
        if (capacity == static_cast<std::size_t>(0))
        {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    void write(const T& item)
    {
        if (is_full())
        {
            throw std::domain_error("Buffer is full");
        }

        m_data[m_tail] = item;
        m_tail = next_index(m_tail);
        ++m_size;
    }

    T read()
    {
        if (is_empty())
        {
            throw std::domain_error("Buffer is empty");
        }

        T value = m_data[m_head];
        m_head = next_index(m_head);
        --m_size;
        return value;
    }

    void overwrite(const T& item)
    {
        if (is_full())
        {
            m_data[m_head] = item;
            m_head = next_index(m_head);
            m_tail = next_index(m_tail);
        }
        else
        {
            write(item);
        }
    }

    void clear() noexcept
    {
        m_head = static_cast<std::size_t>(0);
        m_tail = static_cast<std::size_t>(0);
        m_size = static_cast<std::size_t>(0);
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (m_size == static_cast<std::size_t>(0));
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return (m_size == m_capacity);
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return m_capacity;
    }

private:
    [[nodiscard]] std::size_t next_index(std::size_t index) const noexcept
    {
        return ((index + static_cast<std::size_t>(1)) % m_capacity);
    }

    std::size_t m_capacity;
    std::vector<T> m_data;
    std::size_t m_head;
    std::size_t m_tail;
    std::size_t m_size;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
