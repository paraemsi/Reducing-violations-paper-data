#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

// Use std::size_t directly to avoid type alias issues in template signature
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity);

    void write(const T& item);
    void overwrite(const T& item);
    T read();
    void clear();
    bool is_empty() const;
    bool is_full() const;
    std::size_t size() const;
    std::size_t capacity() const;

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};

// Explicit template instantiations for common types (if needed)
// extern template class circular_buffer<std::int32_t>;
// extern template class circular_buffer<char>;

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
