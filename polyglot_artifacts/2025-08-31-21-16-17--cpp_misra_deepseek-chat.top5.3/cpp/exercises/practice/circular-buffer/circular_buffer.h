#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    std::uint32_t head;
    std::uint32_t tail;
    std::uint32_t count;
    std::uint32_t capacity_;

public:
    explicit circular_buffer(std::uint32_t size);
    T read();
    void write(const T& data);
    void overwrite(const T& data);
    void clear();
    std::uint32_t capacity() const { return capacity_; }
    std::uint32_t size() const { return count; }
    bool empty() const { return (count == 0U); }
    bool full() const { return (count == capacity_); }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
