#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

using size_type = std::size_t;

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity);

    void write(const T& item);
    void overwrite(const T& item);
    T read();
    bool is_empty() const;
    bool is_full() const;
    void clear();

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
