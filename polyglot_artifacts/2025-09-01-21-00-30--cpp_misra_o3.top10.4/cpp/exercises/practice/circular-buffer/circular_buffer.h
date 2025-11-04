#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace circular_buffer {

template<typename T>
class CircularBuffer
{
public:
    explicit CircularBuffer(std::size_t capacity) :
        m_storage(capacity),
        m_capacity(capacity),
        m_head(0U),
        m_tail(0U),
        m_full(false)
    {
        if (m_capacity == 0U)
        {
            throw std::invalid_argument("capacity must be greater than 0");
        }
    }

    void write(const T& item)
    {
        if (is_full())
        {
            throw std::domain_error("buffer is full");
        }

        m_storage[m_tail] = item;
        advance_tail();
    }

    void overwrite(const T& item)
    {
        if (is_full())
        {
            /* buffer full: discard oldest element by moving head forward */
            m_storage[m_tail] = item;
            advance_tail();                     /* tail moves first          */
            m_head = m_tail;                    /* head follows to next slot */
        }
        else
        {
            write(item);
        }
    }

    T read()
    {
        if (is_empty())
        {
            throw std::domain_error("buffer is empty");
        }

        T value = std::move(m_storage[m_head]);
        advance_head();
        return value;
    }

    void clear() noexcept
    {
        m_head = 0U;
        m_tail = 0U;
        m_full = false;
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (!m_full) && (m_head == m_tail);
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return m_full;
    }

    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return m_capacity;
    }

private:
    void advance_head() noexcept
    {
        m_head = (m_head + static_cast<std::size_t>(1U)) % m_capacity;
        m_full = false;
    }

    void advance_tail() noexcept
    {
        m_tail = (m_tail + static_cast<std::size_t>(1U)) % m_capacity;
        if (m_tail == m_head)
        {
            m_full = true;   /* buffer has become full */
        }
    }

    std::vector<T> m_storage;
    std::size_t m_capacity;
    std::size_t m_head;
    std::size_t m_tail;
    bool m_full;
};

template<typename T>
class circular_buffer final : public CircularBuffer<T>
{
public:
    explicit circular_buffer(std::size_t capacity) :
        CircularBuffer<T>(capacity)
    {
        /* Delegates all behavior to the base template */
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
