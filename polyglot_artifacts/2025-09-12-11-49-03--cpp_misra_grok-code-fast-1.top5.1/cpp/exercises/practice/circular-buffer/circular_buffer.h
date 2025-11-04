#include <cstdint>
#include <vector>
#include <stdexcept>

namespace circular_buffer {

template<typename T>
class circular_buffer {
public:
    using value_type = T;
    using size_type = std::size_t;

    explicit circular_buffer(size_type capacity);
    void write(value_type value);
    value_type read();
    void overwrite(value_type value);
    void clear();
    bool empty() const;
    bool full() const;

private:
    std::vector<value_type> buffer_;
    size_type head_;
    size_type tail_;
    size_type size_;
    size_type capacity_;
};

}  // namespace circular_buffer
