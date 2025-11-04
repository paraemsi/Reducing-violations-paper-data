/*  Implementation file for the circular_buffer template.
 *  Included at the end of circular_buffer.h.
 */

namespace circular_buffer
{

template<typename T>
inline circular_buffer<T>::circular_buffer(std::size_t capacity) :
    m_storage(capacity),
    m_head(static_cast<std::size_t>(0U)),
    m_tail(static_cast<std::size_t>(0U)),
    m_full(false)
{
    if (capacity == static_cast<std::size_t>(0U)) {
        throw std::invalid_argument("Capacity must be greater than zero");
    }
}

template<typename T>
inline void circular_buffer<T>::write(const T& item)
{
    if (full()) {
        throw std::domain_error("Buffer is full");
    }

    m_storage[m_head] = item;
    m_head = advance(m_head);

    if (m_head == m_tail) {
        m_full = true;
    }
}

template<typename T>
inline void circular_buffer<T>::overwrite(const T& item)
{
    if (full()) {
        /* Overwrite the oldest element */
        m_storage[m_head] = item;
        m_head = advance(m_head);
        m_tail = advance(m_tail);
    } else {
        write(item);
    }
}

template<typename T>
inline T circular_buffer<T>::read()
{
    if (empty()) {
        throw std::domain_error("Buffer is empty");
    }

    const T value = m_storage[m_tail];
    m_full = false;
    m_tail = advance(m_tail);

    return value;
}

template<typename T>
inline void circular_buffer<T>::clear() noexcept
{
    m_head = m_tail;
    m_full = false;
}

template<typename T>
inline bool circular_buffer<T>::empty() const noexcept
{
    return (!m_full) && (m_head == m_tail);
}

template<typename T>
inline bool circular_buffer<T>::full() const noexcept
{
    return m_full;
}

template<typename T>
inline std::size_t circular_buffer<T>::size() const noexcept
{
    if (m_full) {
        return m_storage.size();
    }

    if (m_head >= m_tail) {
        return (m_head - m_tail);
    }

    return (m_storage.size() - (m_tail - m_head));
}

template<typename T>
inline std::size_t circular_buffer<T>::capacity() const noexcept
{
    return m_storage.size();
}

template<typename T>
inline std::size_t circular_buffer<T>::advance(std::size_t idx) const noexcept
{
    const std::size_t next = (idx + static_cast<std::size_t>(1U));

    if (next == m_storage.size()) {
        return static_cast<std::size_t>(0U);
    }
    return next;
}

} // namespace circular_buffer
