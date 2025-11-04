#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t capacity;
    size_t size;
    size_t head;
    size_t tail;
    
public:
    explicit circular_buffer(size_t capacity);
    T read();
    void write(const T& data);
    void overwrite(const T& data);
    void clear();
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
