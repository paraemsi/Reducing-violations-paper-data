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
        : buffer_(capacity), capacity_(capacity), size_(0U), read_pos_(0U), write_pos_(0U) {
        if (capacity == 0U) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    T read() {
        if (size_ == 0U) {
            throw std::runtime_error("Buffer is empty");
        }
        T value = buffer_[read_pos_];
        read_pos_ = ((read_pos_ + 1U) % capacity_);
        --size_;
        return value;
    }

    void write(const T& value) {
        if (size_ == capacity_) {
            throw std::runtime_error("Buffer is full");
        }
        buffer_[write_pos_] = value;
        write_pos_ = ((write_pos_ + 1U) % capacity_);
        ++size_;
    }

    void overwrite(const T& value) {
        if (size_ < capacity_) {
            write(value);
        } else {
            buffer_[write_pos_] = value;
            write_pos_ = ((write_pos_ + 1U) % capacity_);
            read_pos_ = ((read_pos_ + 1U) % capacity_);
        }
    }

    void clear() {
        size_ = 0U;
        read_pos_ = 0U;
        write_pos_ = 0U;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t read_pos_;
    std::size_t write_pos_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
