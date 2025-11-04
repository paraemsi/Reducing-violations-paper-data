#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(size_t capacity) 
        : capacity_(capacity), buffer_(capacity), size_(0), head_(0), tail_(0) {
    }
    
    T read() {
        if (empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }
    
    void write(const T& data) {
        if (full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = data;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }
    
    void overwrite(const T& data) {
        if (full()) {
            // Overwrite the oldest element (head)
            read();
        }
        write(data);
    }
    
    void clear() {
        size_ = 0;
        head_ = 0;
        tail_ = 0;
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    bool full() const {
        return size_ == capacity_;
    }
    
private:
    size_t capacity_;
    std::vector<T> buffer_;
    size_t size_;
    size_t head_;
    size_t tail_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
