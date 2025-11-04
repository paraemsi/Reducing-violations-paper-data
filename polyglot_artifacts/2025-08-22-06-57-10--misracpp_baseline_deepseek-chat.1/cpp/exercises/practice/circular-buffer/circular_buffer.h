#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
private:
    std::vector<T> buffer;
    size_t capacity;
    size_t size;
    size_t read_pos;
    size_t write_pos;

public:
    explicit circular_buffer(size_t capacity);
    T read();
    void write(const T& data);
    void overwrite(const T& data);
    void clear();
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
