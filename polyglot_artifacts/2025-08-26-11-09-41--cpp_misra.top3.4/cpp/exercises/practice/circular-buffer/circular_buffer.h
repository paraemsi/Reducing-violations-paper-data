#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

using buffer_size_t = std::size_t;

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(buffer_size_t capacity);

    void write(T const& item);
    void overwrite(T const& item);
    T read();
    void clear();
    bool is_empty() const;
    bool is_full() const;
    buffer_size_t size() const;
    buffer_size_t capacity() const;

private:
    std::vector<T> buffer_;
    buffer_size_t capacity_;
    buffer_size_t head_;
    buffer_size_t tail_;
    buffer_size_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
