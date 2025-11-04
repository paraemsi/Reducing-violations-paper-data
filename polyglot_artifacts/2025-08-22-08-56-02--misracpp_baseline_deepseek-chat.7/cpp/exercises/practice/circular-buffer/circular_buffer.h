#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(size_t capacity) 
        : buffer_(capacity), capacity_(capacity), size_(0), read_pos_(0), write_pos_(0) {}
    
    T read() {
        if (size_ == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[read_pos_];
        read_pos_ = (read_pos_ + 1) % capacity_;
        size_--;
        return value;
    }
    
    void write(const T& value) {
        if (size_ == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[write_pos_] = value;
        write_pos_ = (write_pos_ + 1) % capacity_;
        size_++;
    }
    
    void overwrite(const T& value) {
        if (size_ < capacity_) {
            write(value);
        } else {
            // Buffer is full, overwrite the oldest element
            buffer_[write_pos_] = value;
            write_pos_ = (write_pos_ + 1) % capacity_;
            read_pos_ = (read_pos_ + 1) % capacity_;
            // Size remains at capacity_
        }
    }
    
    void clear() {
        size_ = 0;
        read_pos_ = 0;
        write_pos_ = 0;
    }

private:
    std::vector<T> buffer_;
    size_t capacity_;
    size_t size_;
    size_t read_pos_;
    size_t write_pos_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
