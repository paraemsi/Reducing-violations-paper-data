#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {


/*
 * circular_buffer
 *  A fixed-capacity ring buffer that supports:
 *    • write            – store a new element, throws if the buffer is full
 *    • overwrite        – store a new element, replacing the oldest if full
 *    • read             – remove and return the oldest element, throws if empty
 *    • clear            – remove all elements
 *    • query helpers    – is_empty / is_full / size / max_size
 *
 *  The implementation is header-only to keep all template code in one
 *  translation unit per MISRA guidance and to avoid linkage pitfalls.
 */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : m_buffer(capacity),
          m_head(0U),
          m_tail(0U),
          m_count(0U),
          m_capacity(capacity) {
        if (m_capacity == 0U) {
            throw std::invalid_argument("capacity must be > 0");
        }
    }

    void write(const T& item) {
        if (is_full()) {
            throw std::domain_error("buffer is full");
        } else {
            m_buffer[m_head] = item;
            m_head = ((m_head + 1U) % m_capacity);
            ++m_count;
        }
    }

    void overwrite(const T& item) {
        if (is_full()) {
            /* overwrite the oldest element */
            m_buffer[m_head] = item;
            m_head = ((m_head + 1U) % m_capacity);
            m_tail = m_head;
            /* m_count remains unchanged because the buffer stays full */
        } else {
            write(item);
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("buffer is empty");
        } else {
            T value = m_buffer[m_tail];
            m_tail = ((m_tail + 1U) % m_capacity);
            --m_count;
            return value;
        }
    }

    void clear() noexcept {
        m_head = 0U;
        m_tail = 0U;
        m_count = 0U;
        /* No need to touch element storage */
    }

    [[nodiscard]] bool is_empty() const noexcept {
        return (m_count == 0U);
    }

    [[nodiscard]] bool is_full() const noexcept {
        return (m_count == m_capacity);
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return m_count;
    }

    [[nodiscard]] std::size_t max_size() const noexcept {
        return m_capacity;
    }

private:
    std::vector<T> m_buffer;
    std::size_t    m_head;
    std::size_t    m_tail;
    std::size_t    m_count;
    std::size_t    m_capacity;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
