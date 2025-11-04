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
    explicit circular_buffer(size_type capacity);

    void write(const T& item);
    void overwrite(const T& item);
    T read();
    void clear();
    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_full() const;
    [[nodiscard]] size_type capacity() const;
    [[nodiscard]] size_type size() const;

private:
    std::vector<T> buffer_;
    size_type capacity_;
    size_type head_;
    size_type tail_;
    size_type count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
