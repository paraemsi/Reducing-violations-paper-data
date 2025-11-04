#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    using value_type = T;
    using size_type = std::size_t;

    class buffer_full;
    class buffer_empty;

    explicit circular_buffer(size_type capacity);

    void write(const value_type& value);
    value_type read();
    void clear();
    void overwrite(const value_type& value);

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_full() const;

private:
    std::vector<value_type> m_buffer;
    size_type m_capacity;
    size_type m_head;
    size_type m_tail;
    bool m_full;
};

template <typename T>
class circular_buffer<T>::buffer_full : public std::runtime_error {
public:
    buffer_full() : std::runtime_error("circular buffer is full") {}
};

template <typename T>
class circular_buffer<T>::buffer_empty : public std::runtime_error {
public:
    buffer_empty() : std::runtime_error("circular buffer is empty") {}
};

template <typename T>
circular_buffer<T>::circular_buffer(size_type capacity)
    : m_buffer(capacity),
      m_capacity(capacity),
      m_head(0U),
      m_tail(0U),
      m_full(false)
{
}

template <typename T>
void circular_buffer<T>::write(const value_type& value)
{
    if (is_full()) {
        throw buffer_full();
    }
    m_buffer[m_head] = value;
    m_head = (m_head + 1U) % m_capacity;
    if (m_head == m_tail) {
        m_full = true;
    }
}

template <typename T>
typename circular_buffer<T>::value_type circular_buffer<T>::read()
{
    if (is_empty()) {
        throw buffer_empty();
    }
    value_type value = m_buffer[m_tail];
    m_full = false;
    m_tail = (m_tail + 1U) % m_capacity;
    return value;
}

template <typename T>
void circular_buffer<T>::clear()
{
    m_head = 0U;
    m_tail = 0U;
    m_full = false;
    for (size_type i = 0U; i < m_capacity; ++i) {
        m_buffer[i] = value_type();
    }
}

template <typename T>
void circular_buffer<T>::overwrite(const value_type& value)
{
    if (is_full()) {
        m_buffer[m_head] = value;
        m_head = (m_head + 1U) % m_capacity;
        m_tail = m_head;
        m_full = true;
    } else {
        write(value);
    }
}

template <typename T>
bool circular_buffer<T>::is_empty() const
{
    return ((m_head == m_tail) && (!m_full));
}

template <typename T>
bool circular_buffer<T>::is_full() const
{
    return m_full;
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
