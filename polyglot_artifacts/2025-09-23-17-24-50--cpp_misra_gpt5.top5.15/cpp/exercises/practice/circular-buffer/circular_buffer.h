#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : m_buf(capacity),
          m_head(static_cast<std::size_t>(0U)),
          m_tail(static_cast<std::size_t>(0U)),
          m_size(static_cast<std::size_t>(0U)) {
        if ((capacity == static_cast<std::size_t>(0U))) {
            throw std::invalid_argument("circular_buffer capacity must be > 0");
        }
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("cannot write: buffer is full");
        } else {
            m_buf[m_tail] = value;
            m_tail = ((m_tail + static_cast<std::size_t>(1U)) % m_buf.size());
            m_size = (m_size + static_cast<std::size_t>(1U));
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("cannot read: buffer is empty");
        } else {
            T value = m_buf[m_head];
            m_head = ((m_head + static_cast<std::size_t>(1U)) % m_buf.size());
            m_size = (m_size - static_cast<std::size_t>(1U));
            return value;
        }
    }

    void overwrite(const T& value) {
        if (full()) {
            // Buffer is full: write at tail (next write position), then advance both head and tail.
            m_buf[m_tail] = value;
            m_tail = ((m_tail + static_cast<std::size_t>(1U)) % m_buf.size());
            m_head = ((m_head + static_cast<std::size_t>(1U)) % m_buf.size());
            // m_size remains at capacity
        } else {
            write(value);
        }
    }

    void clear() noexcept {
        m_head = static_cast<std::size_t>(0U);
        m_tail = static_cast<std::size_t>(0U);
        m_size = static_cast<std::size_t>(0U);
    }

    bool empty() const noexcept {
        return (m_size == static_cast<std::size_t>(0U));
    }

    bool full() const noexcept {
        return (m_size == m_buf.size());
    }

    std::size_t capacity() const noexcept {
        return m_buf.size();
    }

    std::size_t size() const noexcept {
        return m_size;
    }

private:
    std::vector<T> m_buf;
    std::size_t m_head;
    std::size_t m_tail;
    std::size_t m_size;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
