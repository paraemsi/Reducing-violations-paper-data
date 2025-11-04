#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <string>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::uint32_t capacity);
    T read();
    void write(const T& data);
    void overwrite(const T& data);
    void clear();
    
private:
    std::vector<T> buffer;
    std::uint32_t head;
    std::uint32_t tail;
    std::uint32_t count;
    std::uint32_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
