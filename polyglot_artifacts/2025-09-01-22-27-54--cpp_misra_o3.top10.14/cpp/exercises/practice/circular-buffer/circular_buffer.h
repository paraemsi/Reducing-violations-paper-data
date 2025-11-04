#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace circular_buffer {

/*
 * Generic fixed-capacity circular buffer that stores elements of type T.
 * All operations have constant complexity.
 */
template <typename T>
class circular_buffer
{
public:
    explicit circular_buffer(std::size_t capacity)
        : m_storage(capacity)
    {
        if (capacity == std::size_t{0U}) {
            throw std::invalid_argument(std::string{"Capacity must be greater than zero"});
        }
    }

    /*
     * Insert value at the logical end of the buffer.
     * Throws std::domain_error if the buffer is full.
     */
    void write(const T& value)
    {
        if (full()) {
            throw std::domain_error(std::string{"Buffer is full"});
        }

        m_storage[m_head] = value;
        m_head = advance(m_head);

        if (m_head == m_tail) {
            m_full = true;
        }
    }

    /*
     * Insert value, overwriting the oldest element if the buffer is full.
     */
    void overwrite(const T& value)
    {
        if (full()) {
            /* overwrite and move both head and tail */
            m_storage[m_head] = value;
            m_head = advance(m_head);
            m_tail = m_head;
        } else {
            write(value);
        }
    }

    /*
     * Remove and return the oldest element.
     * Throws std::domain_error if the buffer is empty.
     */
    T read()
    {
        if (empty()) {
            throw std::domain_error(std::string{"Buffer is empty"});
        }

        T value = m_storage[m_tail];
        m_tail = advance(m_tail);
        m_full = false;
        return value;
    }

    /*
     * Reset the buffer to the empty state.
     */
    void clear() noexcept
    {
        m_head = std::size_t{0U};
        m_tail = std::size_t{0U};
        m_full = false;
    }

private:
    std::vector<T>      m_storage;
    std::size_t         m_head {0U};
    std::size_t         m_tail {0U};
    bool                m_full {false};

    [[nodiscard]] bool empty() const noexcept
    {
        return (!m_full) && (m_head == m_tail);
    }

    [[nodiscard]] bool full() const noexcept
    {
        return m_full;
    }

    [[nodiscard]] std::size_t advance(std::size_t idx) const noexcept
    {
        return (idx + std::size_t{1U}) % m_storage.size();
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
