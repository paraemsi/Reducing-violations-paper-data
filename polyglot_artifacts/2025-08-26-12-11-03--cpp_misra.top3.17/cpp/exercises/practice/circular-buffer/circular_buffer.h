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
    bool is_empty() const;
    bool is_full() const;
    size_type capacity() const;
    size_type size() const;

private:
    std::vector<T> buffer_;
    size_type head_;
    size_type tail_;
    size_type count_;
    size_type max_size_;
};

/* Explicit instantiations for common types (add more as needed)
 * For templates, extern template declarations should only be used if there is a matching explicit instantiation
 * in a single translation unit. If not, remove these lines to avoid linker errors.
 */

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
