#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>         // for std::size_t
#include <stdexcept>
#include <utility>
#include <vector>
#include <optional>

namespace circular_buffer {

template <typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::uint32_t capacity)
        : m_buffer(static_cast<std::size_t>(capacity)),
          m_capacity(capacity),
          m_head(0U),
          m_tail(0U),
          m_count(0U)
    {
        if (capacity == 0U) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    void clear() noexcept
    {
        for (auto &slot : m_buffer) {
            slot.reset();
        }
        m_head = 0U;
        m_tail = 0U;
        m_count = 0U;
    }

    bool empty() const noexcept
    {
        return (m_count == 0U);
    }

    bool full() const noexcept
    {
        return (m_count == m_capacity);
    }

    void write(const T& value)
    {
        if (full()) {
            throw std::domain_error("Buffer is full");
        }
        push_value(value);
    }

    void write(T&& value)
    {
        if (full()) {
            throw std::domain_error("Buffer is full");
        }
        push_value(std::move(value));
    }

    void overwrite(const T& value)
    {
        if (full()) {
            static_cast<void>(pop_value());
        }
        push_value(value);
    }

    void overwrite(T&& value)
    {
        if (full()) {
            static_cast<void>(pop_value());
        }
        push_value(std::move(value));
    }

    T read()
    {
        if (empty()) {
            throw std::domain_error("Buffer is empty");
        }
        return pop_value();
    }

private:
    template <typename V>
    void push_value(V&& value)
    {
        auto &slot = m_buffer[static_cast<std::size_t>(m_tail)];
        slot.reset();
        slot.emplace(std::forward<V>(value));
        m_tail = ((m_tail + static_cast<std::uint32_t>(1U)) % m_capacity);
        ++m_count;
    }

    T pop_value()
    {
        std::optional<T>& slot = m_buffer[static_cast<std::size_t>(m_head)];
        T value = std::move(*slot);
        slot.reset();
        m_head = ((m_head + static_cast<std::uint32_t>(1U)) % m_capacity);
        --m_count;
        return value;
    }

    std::vector<std::optional<T>> m_buffer;
    std::uint32_t m_capacity;
    std::uint32_t m_head;
    std::uint32_t m_tail;
    std::uint32_t m_count;
};


}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
