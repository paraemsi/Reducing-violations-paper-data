#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class CircularBuffer
{
public:
    explicit CircularBuffer(std::size_t capacity);

    void write(const T& value);
    void overwrite(const T& value);
    T read();
    void clear();

    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] bool full() const noexcept;

private:
    std::vector<T> m_storage;
    std::size_t    m_capacity;
    std::size_t    m_head; // next position to write
    std::size_t    m_tail; // next position to read
    std::size_t    m_size; // current number of elements
};

template <typename U>
using circular_buffer = CircularBuffer<U>;

}  // namespace circular_buffer

#include "circular_buffer.tpp"

#endif // CIRCULAR_BUFFER_H
