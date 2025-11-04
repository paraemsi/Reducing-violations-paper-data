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
        : m_buffer(capacity),
          m_capacity(capacity),
          m_head(0U),
          m_tail(0U),
          m_size(0U) {
        if (capacity == 0U) {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }

    void clear() noexcept {
        m_head = 0U;
        m_tail = 0U;
        m_size = 0U;
    }

    void write(const T& item) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        } else {
            m_buffer[m_tail] = item;
            m_tail = (m_tail + static_cast<std::size_t>(1U)) % m_capacity;
            ++m_size;
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        } else {
            T value = m_buffer[m_head];
            m_head = (m_head + static_cast<std::size_t>(1U)) % m_capacity;
            --m_size;
            return value;
        }
    }

    void overwrite(const T& item) {
        if (is_full()) {
            /* overwrite the oldest element that is currently at m_head */
            m_buffer[m_head] = item;
            m_head = (m_head + static_cast<std::size_t>(1U)) % m_capacity;
            m_tail = m_head;  /* head and tail move together when buffer stays full */
            /* m_size is unchanged – buffer remains full */
        } else {
            write(item);
        }
    }

private:
    [[nodiscard]] bool is_empty() const noexcept {
        return (m_size == 0U);
    }

    [[nodiscard]] bool is_full() const noexcept {
        return (m_size == m_capacity);
    }

    std::vector<T> m_buffer;
    std::size_t    m_capacity;
    std::size_t    m_head;
    std::size_t    m_tail;
    std::size_t    m_size;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
