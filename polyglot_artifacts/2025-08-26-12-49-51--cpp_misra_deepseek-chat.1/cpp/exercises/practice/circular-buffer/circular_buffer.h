#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <string>

namespace circular_buffer {

// Define an alias for the index type to follow MISRA rules
using index_t = std::uint32_t;

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    index_t head;
    index_t tail;
    index_t count;
    index_t capacity;
    
public:
    explicit circular_buffer(index_t size);
    T read();
    void write(const T& data);
    void overwrite(const T& data);
    void clear();
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
