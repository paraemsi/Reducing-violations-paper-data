#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::uint32_t capacity);
    T read();
    void write(const T& data);
    void overwrite(const T& data);
    void clear();
    std::uint32_t size() const;
    std::uint32_t capacity() const;
    bool empty() const;
    bool full() const;

private:
    std::vector<T> buffer_;
    std::uint32_t head_;
    std::uint32_t tail_;
    std::uint32_t count_;
    std::uint32_t capacity_;
};

}  // namespace circular_buffer

#include "circular_buffer.tpp"

#endif // CIRCULAR_BUFFER_H
