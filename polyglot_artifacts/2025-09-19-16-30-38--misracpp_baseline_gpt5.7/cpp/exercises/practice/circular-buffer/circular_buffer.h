#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity), capacity_(capacity), head_(0), size_(0) {
            if (capacity_ == 0) {
                throw std::invalid_argument("circular_buffer capacity must be greater than 0");
            }
        }

    T read() {
        if (size_ == 0) {
            throw std::domain_error("Empty buffer");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (size_ == capacity_) {
            throw std::domain_error("Full buffer");
        }
        std::size_t tail = (head_ + size_) % capacity_;
        buffer_[tail] = value;
        ++size_;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return;
        }
        if (size_ == capacity_) {
            buffer_[head_] = value;
            head_ = (head_ + 1) % capacity_;
        } else {
            write(value);
        }
    }

    void clear() {
        head_ = 0;
        size_ = 0;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
