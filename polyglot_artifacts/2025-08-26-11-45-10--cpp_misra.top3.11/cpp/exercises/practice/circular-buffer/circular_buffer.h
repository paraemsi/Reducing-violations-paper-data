#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

using index_t = std::size_t;

template <typename T>
class CircularBuffer;

template <typename T>
class circular_buffer;

template <typename T>
using circular_buffer = CircularBuffer<T>;

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(index_t capacity);

    void write(const T& item);
    void overwrite(const T& item);
    T read();
    void clear();
    bool is_empty() const;
    bool is_full() const;
    index_t size() const;
    index_t capacity() const;

private:
    std::vector<T> buffer_;
    index_t capacity_;
    index_t head_;
    index_t tail_;
    index_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
