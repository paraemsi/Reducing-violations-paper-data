#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(size_t capacity) 
        : buffer_(capacity), read_pos_(0), write_pos_(0), size_(0), capacity_(capacity) {
    }
    
    T read() {
        if (empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[read_pos_];
        read_pos_ = (read_pos_ + 1) % capacity_;
        --size_;
        return value;
    }
    
    void write(const T& data) {
        if (full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[write_pos_] = data;
        write_pos_ = (write_pos_ + 1) % capacity_;
        ++size_;
    }
    
    void overwrite(const T& data) {
        if (full()) {
            // Write the data to the current write position
            buffer_[write_pos_] = data;
            // Advance write pointer
            write_pos_ = (write_pos_ + 1) % capacity_;
            // The oldest element is now the next one after the current read position
            read_pos_ = write_pos_;
        } else {
            write(data);
        }
    }
    
    void clear() {
        read_pos_ = 0;
        write_pos_ = 0;
        size_ = 0;
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    bool full() const {
        return size_ == capacity_;
    }
    
private:
    std::vector<T> buffer_;
    size_t read_pos_;
    size_t write_pos_;
    size_t size_;
    size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
