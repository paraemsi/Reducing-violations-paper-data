#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(const std::size_t capacity) 
        : buffer_(capacity), head_(0), tail_(0), full_(false), capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than zero");
        }
    }
    
    T read() {
        if (isEmpty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1U) % capacity_;
        full_ = false;
        return value;
    }
    
    void write(const T& data) {
        if (isFull()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = data;
        tail_ = (tail_ + 1U) % capacity_;
        full_ = (head_ == tail_);
    }
    
    void clear() {
        head_ = 0;
        tail_ = 0;
        full_ = false;
    }
    
    void overwrite(const T& data) {
        if (isFull()) {
            // Make space by moving head forward
            head_ = (head_ + 1U) % capacity_;
        }
        buffer_[tail_] = data;
        tail_ = (tail_ + 1U) % capacity_;
        full_ = (head_ == tail_);
    }
    
private:
    bool isEmpty() const {
        return (!full_ && (head_ == tail_));
    }
    
    bool isFull() const {
        return full_;
    }
    
    std::vector<T> buffer_;
    std::uint32_t head_;
    std::uint32_t tail_;
    bool full_;
    std::uint32_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
