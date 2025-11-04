#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdexcept>
#include <vector>
#include <cstddef>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity) 
        : buffer_(capacity), capacity_(capacity), size_(0), read_pos_(0), write_pos_(0) {
        if (capacity == 0) {
            throw std::domain_error("Buffer capacity must be greater than zero");
        }
    }

    void write(const T& value) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[write_pos_] = value;
        write_pos_ = (write_pos_ + 1) % capacity_;
        size_++;
    }

    void overwrite(const T& value) {
        bool was_full = is_full();
        
        buffer_[write_pos_] = value;
        write_pos_ = (write_pos_ + 1) % capacity_;
        
        if (was_full) {
            // If buffer was full, move read position forward (overwriting oldest)
            read_pos_ = (read_pos_ + 1) % capacity_;
        } else {
            size_++;
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[read_pos_];
        read_pos_ = (read_pos_ + 1) % capacity_;
        size_--;
        return value;
    }

    void clear() {
        size_ = 0;
        read_pos_ = 0;
        write_pos_ = 0;
    }

    bool is_empty() const {
        return size_ == 0;
    }

    bool is_full() const {
        return size_ == capacity_;
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
