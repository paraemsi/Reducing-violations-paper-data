#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity) 
        : buffer_(capacity), capacity_(capacity), size_(0), head_(0), tail_(0) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    T read() {
        if (size_ == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = ((head_ + 1) % capacity_);
        size_--;
        return value;
    }

    void write(const T& value) {
        if (size_ == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = value;
        tail_ = ((tail_ + 1) % capacity_);
        size_++;
    }

    void overwrite(const T& value) {
        if (size_ == capacity_) {
            // Write the value to the current tail position, which is where the next element would be added
            buffer_[tail_] = value;
            // Move both head and tail forward to maintain the circular nature
            head_ = ((head_ + 1) % capacity_);
            tail_ = ((tail_ + 1) % capacity_);
        } else {
            write(value);
        }
    }

    void clear() {
        size_ = 0;
        head_ = 0;
        tail_ = 0;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t head_;
    std::size_t tail_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
