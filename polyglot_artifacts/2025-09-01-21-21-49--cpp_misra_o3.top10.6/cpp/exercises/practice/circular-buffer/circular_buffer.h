#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/*
 * CircularBuffer
 * A fixed-capacity ring buffer providing:
 *  • write()     – append element, throws if full
 *  • overwrite() – append element, replaces oldest when full
 *  • read()      – remove & return oldest element, throws if empty
 *  • clear(), is_empty(), is_full()
 */
template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::uint32_t capacity) :
        m_buffer(static_cast<std::size_t>(capacity)),
        m_capacity(capacity),
        m_head(static_cast<std::uint32_t>(0U)),
        m_tail(static_cast<std::uint32_t>(0U)),
        m_size(static_cast<std::uint32_t>(0U))
    {
        if (capacity == static_cast<std::uint32_t>(0U)) {
            /*  The specification requires construction of a zero-length
             *  buffer to raise std::domain_error.
             */
            throw std::domain_error("capacity must be > 0");
        }
    }

    void clear() noexcept
    {
        m_head = static_cast<std::uint32_t>(0U);
        m_tail = static_cast<std::uint32_t>(0U);
        m_size = static_cast<std::uint32_t>(0U);
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (m_size == static_cast<std::uint32_t>(0U));
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return (m_size == m_capacity);
    }

    void write(const T& item)
    {
        if (is_full()) {
            throw std::domain_error("circular buffer is full");
        }

        m_buffer[static_cast<std::size_t>(m_head)] = item;
        m_head = advance(m_head);
        ++m_size;
    }

    void overwrite(const T& item)
    {
        if (is_full()) {
            m_buffer[static_cast<std::size_t>(m_head)] = item;
            m_head = advance(m_head);
            m_tail = advance(m_tail);
        } else {
            write(item);
        }
    }

    T read()
    {
        if (is_empty()) {
            throw std::domain_error("circular buffer is empty");
        }

        T value = m_buffer[static_cast<std::size_t>(m_tail)];
        m_tail = advance(m_tail);
        --m_size;
        return value;
    }

private:
    std::vector<T>   m_buffer;
    std::uint32_t    m_capacity;
    std::uint32_t    m_head;     // next write position
    std::uint32_t    m_tail;     // next read position
    std::uint32_t    m_size;     // current element count

    [[nodiscard]] std::uint32_t advance(std::uint32_t index) const noexcept
    {
        return static_cast<std::uint32_t>(
            ((index + static_cast<std::uint32_t>(1U)) % m_capacity));
    }
};

/*  Explicit extern instantiation declaration to match the definition
 *  provided in circular_buffer.cpp and avoid multiple definition
 *  across translation units.
 */
extern template class circular_buffer<std::int32_t>;

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
