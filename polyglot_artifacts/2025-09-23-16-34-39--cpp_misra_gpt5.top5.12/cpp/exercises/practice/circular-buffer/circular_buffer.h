#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : m_buf(capacity),
          m_capacity(capacity),
          m_head(static_cast<std::size_t>(0U)),
          m_size(static_cast<std::size_t>(0U)) {
        if (capacity == static_cast<std::size_t>(0U)) {
            throw std::invalid_argument("capacity must be > 0");
        } else {
            // no-op
        }
    }

    circular_buffer& operator=(const circular_buffer& rhs) {
        if (this != &rhs) {
            if (m_capacity != rhs.m_capacity) {
                throw std::invalid_argument("capacity mismatch");
            } else {
                // no-op
            }
            m_buf = rhs.m_buf;
            m_head = rhs.m_head;
            m_size = rhs.m_size;
        } else {
            // self-assign, no-op
        }
        return *this;
    }

    circular_buffer& operator=(circular_buffer&& rhs) {
        if (this != &rhs) {
            if (m_capacity != rhs.m_capacity) {
                throw std::invalid_argument("capacity mismatch");
            } else {
                // no-op
            }
            m_buf = std::move(rhs.m_buf);
            m_head = rhs.m_head;
            m_size = rhs.m_size;
        } else {
            // self-assign, no-op
        }
        return *this;
    }

    void clear() noexcept {
        m_head = static_cast<std::size_t>(0U);
        m_size = static_cast<std::size_t>(0U);
    }

    void write(const T& value) {
        if (is_full()) {
            throw std::domain_error("buffer full");
        } else {
            const std::size_t tail = ((m_head + m_size) % m_capacity);
            m_buf[tail] = value;
            m_size = (m_size + static_cast<std::size_t>(1U));
        }
    }

    void write(T&& value) {
        if (is_full()) {
            throw std::domain_error("buffer full");
        } else {
            const std::size_t tail = ((m_head + m_size) % m_capacity);
            m_buf[tail] = std::move(value);
            m_size = (m_size + static_cast<std::size_t>(1U));
        }
    }

    void overwrite(const T& value) {
        if (is_full()) {
            m_buf[m_head] = value;
            m_head = ((m_head + static_cast<std::size_t>(1U)) % m_capacity);
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
        if (is_full()) {
            m_buf[m_head] = std::move(value);
            m_head = ((m_head + static_cast<std::size_t>(1U)) % m_capacity);
        } else {
            write(std::move(value));
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("buffer empty");
        } else {
            T value = std::move(m_buf[m_head]);
            m_head = ((m_head + static_cast<std::size_t>(1U)) % m_capacity);
            m_size = (m_size - static_cast<std::size_t>(1U));
            return value;
        }
    }

    [[nodiscard]] bool is_empty() const noexcept {
        return (m_size == static_cast<std::size_t>(0U));
    }

    [[nodiscard]] bool is_full() const noexcept {
        return (m_size == m_capacity);
    }

    [[nodiscard]] std::size_t capacity() const noexcept {
        return m_capacity;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return m_size;
    }

private:
    std::vector<T> m_buf;
    const std::size_t m_capacity;
    std::size_t m_head;
    std::size_t m_size;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
