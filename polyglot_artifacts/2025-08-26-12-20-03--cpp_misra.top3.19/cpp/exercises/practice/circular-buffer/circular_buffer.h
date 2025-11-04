#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class CircularBuffer {
public:
    using size_type = std::size_t;
public:
    explicit CircularBuffer(size_type capacity);

    void write(const T& item);
    void overwrite(const T& item);
    T read();
    bool is_empty() const;
    bool is_full() const;
    void clear();

private:
    std::vector<T> buffer_;
    size_type capacity_;
    size_type head_;
    size_type tail_;
    size_type count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
