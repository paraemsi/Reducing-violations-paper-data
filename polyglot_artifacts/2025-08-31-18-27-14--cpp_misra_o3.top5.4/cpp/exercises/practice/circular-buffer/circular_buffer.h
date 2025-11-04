#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T, std::size_t N>
class circular_buffer_fixed {
public:
    static_assert(N > static_cast<std::size_t>(0U), "Buffer size must be greater than 0");

    circular_buffer_fixed() noexcept
        : m_head(static_cast<std::size_t>(0U)),
          m_tail(static_cast<std::size_t>(0U)),
          m_count(static_cast<std::size_t>(0U))
    {
    }

    void clear() noexcept
    {
        m_head  = static_cast<std::size_t>(0U);
        m_tail  = static_cast<std::size_t>(0U);
        m_count = static_cast<std::size_t>(0U);
    }

    void write(const T& item)
    {
        if (is_full()) {
            throw std::domain_error("Circular buffer is full");
        }

        m_storage[m_tail] = item;
        m_tail            = (m_tail + static_cast<std::size_t>(1U)) % N;
        ++m_count;
    }

    void overwrite(const T& item)
    {
        if (is_full()) {
            /* Drop the oldest element before writing. */
            (void)read();
        }
        write(item);
    }

    [[nodiscard]] T read()
    {
        if (is_empty()) {
            throw std::domain_error("Circular buffer is empty");
        }

        T value = m_storage[m_head];
        m_head  = (m_head + static_cast<std::size_t>(1U)) % N;
        --m_count;
        return value;
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (m_count == static_cast<std::size_t>(0U));
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return (m_count == N);
    }

private:
    std::array<T, N> m_storage{};
    std::size_t      m_head;
    std::size_t      m_tail;
    std::size_t      m_count;
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : m_storage(capacity),
          m_head(static_cast<std::size_t>(0U)),
          m_tail(static_cast<std::size_t>(0U)),
          m_count(static_cast<std::size_t>(0U)),
          m_capacity(capacity)
    {
        if (capacity == static_cast<std::size_t>(0U)) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    void clear() noexcept
    {
        m_head  = static_cast<std::size_t>(0U);
        m_tail  = static_cast<std::size_t>(0U);
        m_count = static_cast<std::size_t>(0U);
    }

    void write(const T& item)
    {
        if (is_full()) {
            throw std::domain_error("Circular buffer is full");
        }

        m_storage[m_tail] = item;
        m_tail            = (m_tail + static_cast<std::size_t>(1U)) % m_capacity;
        ++m_count;
    }

    void overwrite(const T& item)
    {
        if (is_full()) {
            /* Drop the oldest element before writing. */
            (void)read();
        }
        write(item);
    }

    [[nodiscard]] T read()
    {
        if (is_empty()) {
            throw std::domain_error("Circular buffer is empty");
        }

        T value = m_storage[m_head];
        m_head  = (m_head + static_cast<std::size_t>(1U)) % m_capacity;
        --m_count;
        return value;
    }

    [[nodiscard]] bool is_empty() const noexcept
    {
        return (m_count == static_cast<std::size_t>(0U));
    }

    [[nodiscard]] bool is_full() const noexcept
    {
        return (m_count == m_capacity);
    }

private:
    std::vector<T> m_storage;
    std::size_t    m_head;
    std::size_t    m_tail;
    std::size_t    m_count;
    std::size_t    m_capacity;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
