#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::uint32_t capacity) 
        : buffer_(capacity), head_(0U), tail_(0U), size_(0U), capacity_(capacity) {
    }
    
    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = static_cast<std::uint32_t>((head_ + 1U) % capacity_);
        size_ = static_cast<std::uint32_t>(size_ - 1U);
        return value;
    }
    
    void write(const T& data) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = data;
        tail_ = static_cast<std::uint32_t>((tail_ + 1U) % capacity_);
        size_ = static_cast<std::uint32_t>(size_ + 1U);
    }
    
    void overwrite(const T& data) {
        if (is_full()) {
            // Move head forward to make space, effectively overwriting the oldest element
            head_ = static_cast<std::uint32_t>((head_ + 1U) % capacity_);
            size_ = static_cast<std::uint32_t>(size_ - 1U);
        }
        buffer_[tail_] = data;
        tail_ = static_cast<std::uint32_t>((tail_ + 1U) % capacity_);
        size_ = static_cast<std::uint32_t>(size_ + 1U);
    }
    
    void clear() {
        head_ = 0U;
        tail_ = 0U;
        size_ = 0U;
    }
    
    bool is_empty() const {
        return (size_ == 0U);
    }
    
    bool is_full() const {
        return (size_ == capacity_);
    }
    
private:
    std::vector<T> buffer_;
    std::uint32_t head_;
    std::uint32_t tail_;
    std::uint32_t size_;
    std::uint32_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
