#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstdint>
#include <cstddef>

namespace circular_buffer {

template<typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(std::uint32_t capacity) :
        m_buffer(capacity),
        m_capacity(capacity),
        m_head(0U),
        m_tail(0U),
        m_size(0U)
    {
        /* ensure a non-zero capacity at construction */
        if (capacity == 0U) {
            throw std::invalid_argument("capacity must be greater than 0");
        }
    }

    void write(const T& value) {
        if (is_full()) {
            throw std::domain_error("buffer full");
        }
        m_buffer[static_cast<std::size_t>(m_head)] = value;
        advance_head();
        ++m_size;
    }

    void overwrite(const T& value) {
        if (is_full()) {
            m_buffer[static_cast<std::size_t>(m_head)] = value;
            advance_head();
            /* oldest element overwritten, keep size unchanged */
            advance_tail();
        } else {
            write(value);
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("buffer empty");
        }
        T value = m_buffer[static_cast<std::size_t>(m_tail)];
        advance_tail();
        --m_size;
        return value;
    }

    void clear() noexcept {
        m_head = 0U;
        m_tail = 0U;
        m_size = 0U;
    }

private:
    std::vector<T> m_buffer;
    std::uint32_t m_capacity;
    std::uint32_t m_head;
    std::uint32_t m_tail;
    std::uint32_t m_size;

    bool is_full() const noexcept {
        return (m_size == m_capacity);
    }

    bool is_empty() const noexcept {
        return (m_size == 0U);
    }

    void advance_head() noexcept {
        m_head = ((m_head + static_cast<std::uint32_t>(1U)) % m_capacity);
    }

    void advance_tail() noexcept {
        m_tail = ((m_tail + static_cast<std::uint32_t>(1U)) % m_capacity);
    }
};

template<typename T>
using circular_buffer = CircularBuffer<T>;

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
