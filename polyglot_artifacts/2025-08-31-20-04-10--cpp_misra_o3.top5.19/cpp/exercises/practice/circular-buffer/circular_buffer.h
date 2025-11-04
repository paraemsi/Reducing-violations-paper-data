#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer
{

template <typename T>
class CircularBuffer
{
public:
    explicit CircularBuffer(std::size_t capacity) :
        m_storage(capacity),
        m_head(0U),
        m_tail(0U),
        m_count(0U)
    {
        if (capacity == 0U)
        {
            throw std::domain_error("capacity must be > 0");
        }
    }

    void clear() noexcept
    {
        m_head  = 0U;
        m_tail  = 0U;
        m_count = 0U;
    }

    void write(const T& value)
    {
        if (full())
        {
            throw std::domain_error("Full buffer");
        }
        m_storage[m_tail] = value;
        advance_tail();
    }

    void write(T&& value)
    {
        if (full())
        {
            throw std::domain_error("Full buffer");
        }
        m_storage[m_tail] = std::move(value);
        advance_tail();
    }

    void overwrite(const T& value)
    {
        if (full())
        {
            m_storage[m_head] = value;
            advance_head();
            advance_tail();
        }
        else
        {
            /* Buffer not full: place value at tail without extra full( ) check */
            m_storage[m_tail] = value;
            advance_tail();
        }
    }

    void overwrite(T&& value)
    {
        if (full())
        {
            m_storage[m_head] = std::move(value);
            advance_head();
            advance_tail();
        }
        else
        {
            /* Buffer not full: mimic write without risk of recursion */
            m_storage[m_tail] = std::move(value);
            advance_tail();
        }
    }

    T read()
    {
        if (empty())
        {
            throw std::domain_error("Empty buffer");
        }

        /* Move the value out to support move-only types */
        T value = std::move(m_storage[m_head]);
        advance_head();
        return value;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return (m_count == 0U);
    }

    [[nodiscard]] bool full() const noexcept
    {
        return (m_count == m_storage.size());
    }

private:
    std::vector<T> m_storage;
    std::size_t    m_head;
    std::size_t    m_tail;
    std::size_t    m_count;

    void advance_head() noexcept
    {
        m_head = (m_head + 1U) % m_storage.size();
        --m_count;
    }

    void advance_tail() noexcept
    {
        m_tail = (m_tail + 1U) % m_storage.size();
        ++m_count;
    }
};

template <typename T>
class circular_buffer final : public CircularBuffer<T>
{
public:
    explicit circular_buffer(std::size_t capacity) :
        CircularBuffer<T>(capacity)
    {
    }
};

} // namespace circular_buffer
