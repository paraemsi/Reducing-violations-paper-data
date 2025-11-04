#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>      // for std::size_t
#include <cstdint>      // for fixed–width integer types
#include <stdexcept>    // for std::runtime_error
#include <vector>       // for std::vector
#include <utility>      // for std::move

namespace circular_buffer {

/*
 * Fixed-capacity circular (ring) buffer that meets the behaviour
 * described in the exercise specification.
 *
 * MISRA C++ compliance notes:
 *  - Only fixed-width integer types and std::size_t are used.
 *  - All operator precedences are parenthesised where different.
 *  - Each if/else body is enclosed in a compound statement.
 */
template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity) :
        m_buffer(capacity),
        m_capacity(capacity),
        m_head(static_cast<std::size_t>(0)),
        m_tail(static_cast<std::size_t>(0)),
        m_full(false)
    {
        if (capacity == static_cast<std::size_t>(0))
        {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    void clear() noexcept
    {
        m_head = static_cast<std::size_t>(0);
        m_tail = static_cast<std::size_t>(0);
        m_full = false;
    }

    void write(const T& item)
    {
        if (m_full)
        {
            throw std::domain_error("Buffer is full");
        }

        m_buffer[m_head] = item;
        advance_head();
    }

    void write(T&& item)
    {
        if (m_full)
        {
            throw std::domain_error("Buffer is full");
        }

        m_buffer[m_head] = std::move(item);
        advance_head();
    }

    void overwrite(const T& item)
    {
        if (m_full)
        {
            m_buffer[m_head] = item;
            advance_head();           // head moved first to keep oldest index
            m_tail = m_head;          // oldest element becomes new head
            m_full = true;            // buffer remains full after overwrite
        }
        else
        {
            write(item);
        }
    }

    void overwrite(T&& item)
    {
        if (m_full)
        {
            m_buffer[m_head] = std::move(item);
            advance_head();
            m_tail = m_head;
            m_full = true;            // buffer remains full after overwrite
        }
        else
        {
            write(std::move(item));
        }
    }

    T read()
    {
        if (is_empty())
        {
            throw std::domain_error("Buffer is empty");
        }

        T value = std::move(m_buffer[m_tail]);
        advance_tail();
        return value;
    }

    bool is_empty() const noexcept
    {
        return (m_full == false) && (m_head == m_tail);
    }

    bool is_full() const noexcept
    {
        return m_full;
    }

private:
    std::vector<T>   m_buffer;
    const std::size_t m_capacity;
    std::size_t      m_head;   // next write position
    std::size_t      m_tail;   // oldest element position
    bool             m_full;

    void advance_head() noexcept
    {
        m_head = ((m_head + static_cast<std::size_t>(1)) % m_capacity);
        if (m_head == m_tail)
        {
            m_full = true;
        }
    }

    void advance_tail() noexcept
    {
        m_full = false;
        m_tail = ((m_tail + static_cast<std::size_t>(1)) % m_capacity);
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
