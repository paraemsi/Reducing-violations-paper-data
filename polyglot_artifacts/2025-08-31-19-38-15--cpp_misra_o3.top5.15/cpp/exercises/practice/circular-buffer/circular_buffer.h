#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>      // for std::size_t
#include <cstdint>      // for fixed-width integer aliases
#include <stdexcept>    // for std::runtime_error
#include <vector>       // for std::vector

namespace circular_buffer {

/* Exception raised when attempting to read from an empty buffer */
class buffer_empty_error final : public std::domain_error
{
public:
    buffer_empty_error() : std::domain_error("circular buffer is empty") {}
};

/* Exception raised when attempting to write to a full buffer */
class buffer_full_error final : public std::domain_error
{
public:
    buffer_full_error() : std::domain_error("circular buffer is full") {}
};

/*  A fixed-capacity FIFO structure.
 *  Written in header to keep all template definitions visible to the compiler.
 */
template <typename T>
class circular_buffer final
{
public:
    explicit circular_buffer(std::size_t capacity);

    void write(const T& value);       /* insert – throws buffer_full_error if full               */
    void overwrite(const T& value);   /* insert – overwrites oldest element when buffer is full  */
    T    read();                      /* remove and return oldest – throws buffer_empty_error    */

    void clear() noexcept;

    [[nodiscard]] bool empty()    const noexcept { return (m_count == 0U); }
    [[nodiscard]] bool full()     const noexcept { return (m_count == m_storage.size()); }
    [[nodiscard]] std::size_t size() const noexcept { return m_count; }
    [[nodiscard]] std::size_t capacity() const noexcept { return m_storage.size(); }

private:
    std::vector<T> m_storage;   /* underlying storage – fixed at construction                 */
    std::size_t    m_start {0U};/* index of the oldest element                                */
    std::size_t    m_count {0U};/* current number of stored elements                          */
};

/* -------------------------  implementation  ------------------------- */

template <typename T>
circular_buffer<T>::circular_buffer(std::size_t capacity) : m_storage(capacity)
{
    if (capacity == 0U)
    {
        throw std::invalid_argument("capacity must be greater than 0");
    }
}

template <typename T>
void circular_buffer<T>::write(const T& value)
{
    if (full())
    {
        throw buffer_full_error();
    }

    const std::size_t index = (m_start + m_count) % m_storage.size();
    m_storage[index] = value;
    ++m_count;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& value)
{
    if (full())
    {
        /* overwrite the oldest element then advance start pointer */
        m_storage[m_start] = value;
        m_start = (m_start + 1U) % m_storage.size();
    }
    else
    {
        write(value);
    }
}

template <typename T>
T circular_buffer<T>::read()
{
    if (empty())
    {
        throw buffer_empty_error();
    }

    T value = m_storage[m_start];
    m_start = (m_start + 1U) % m_storage.size();
    --m_count;
    return value;
}

template <typename T>
void circular_buffer<T>::clear() noexcept
{
    m_start = 0U;
    m_count = 0U;
}


}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
