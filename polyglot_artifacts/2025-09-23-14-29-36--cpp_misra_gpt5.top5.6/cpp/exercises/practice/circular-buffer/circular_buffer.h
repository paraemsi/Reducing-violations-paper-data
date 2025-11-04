#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <utility>

namespace circular_buffer {

class buffer_full final : public std::domain_error {
public:
    buffer_full() : std::domain_error("circular buffer full") {}
};

class buffer_empty final : public std::domain_error {
public:
    buffer_empty() : std::domain_error("circular buffer empty") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : m_data(capacity),
          m_capacity(capacity),
          m_head(static_cast<std::size_t>(0U)),
          m_tail(static_cast<std::size_t>(0U)),
          m_size(static_cast<std::size_t>(0U))
    {
    }

    void clear() noexcept
    {
        m_head = static_cast<std::size_t>(0U);
        m_tail = static_cast<std::size_t>(0U);
        m_size = static_cast<std::size_t>(0U);
    }

    void write(const T& value)
    {
        if ((m_size == m_capacity)) {
            throw buffer_full{};
        }

        m_data[m_tail] = value;

        if ((m_capacity != static_cast<std::size_t>(0U))) {
            m_tail = ((m_tail + static_cast<std::size_t>(1U)) % m_capacity);
        }

        m_size = (m_size + static_cast<std::size_t>(1U));
    }

    T read()
    {
        if ((m_size == static_cast<std::size_t>(0U))) {
            throw buffer_empty{};
        }

        T value = std::move(m_data[m_head]);

        if ((m_capacity != static_cast<std::size_t>(0U))) {
            m_head = ((m_head + static_cast<std::size_t>(1U)) % m_capacity);
        }

        m_size = (m_size - static_cast<std::size_t>(1U));
        return value;
    }

    void overwrite(const T& value)
    {
        if ((m_capacity == static_cast<std::size_t>(0U))) {
            return;
        }

        if ((m_size == m_capacity)) {
            m_data[m_tail] = value;
            m_tail = ((m_tail + static_cast<std::size_t>(1U)) % m_capacity);
            m_head = ((m_head + static_cast<std::size_t>(1U)) % m_capacity);
        } else {
            m_data[m_tail] = value;
            m_tail = ((m_tail + static_cast<std::size_t>(1U)) % m_capacity);
            m_size = (m_size + static_cast<std::size_t>(1U));
        }
    }

    std::size_t size() const noexcept
    {
        return m_size;
    }

    std::size_t capacity() const noexcept
    {
        return m_capacity;
    }

private:
    std::vector<T> m_data;
    std::size_t m_capacity;
    std::size_t m_head;
    std::size_t m_tail;
    std::size_t m_size;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
