#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <climits>
#include <cstddef>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity) 
        : buffer_(capacity), head_(0U), tail_(0U), count_(0U), capacity_(0U) {
        // Ensure capacity fits in uint32_t
        if (capacity > static_cast<std::size_t>(UINT32_MAX)) {
            throw std::invalid_argument("Capacity too large");
        }
        capacity_ = static_cast<std::uint32_t>(capacity);
    }
    
    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = static_cast<std::uint32_t>((head_ + 1U) % capacity_);
        count_ = static_cast<std::uint32_t>(count_ - 1U);
        return value;
    }
    
    void write(const T& data) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = data;
        tail_ = static_cast<std::uint32_t>((tail_ + 1U) % capacity_);
        count_ = static_cast<std::uint32_t>(count_ + 1U);
    }
    
    void overwrite(const T& data) {
        if (is_full()) {
            // Move head forward to make space, effectively removing the oldest element
            head_ = static_cast<std::uint32_t>((head_ + 1U) % capacity_);
            count_ = static_cast<std::uint32_t>(count_ - 1U);
        }
        buffer_[tail_] = data;
        tail_ = static_cast<std::uint32_t>((tail_ + 1U) % capacity_);
        count_ = static_cast<std::uint32_t>(count_ + 1U);
    }
    
    void clear() {
        head_ = 0U;
        tail_ = 0U;
        count_ = 0U;
    }
    
    bool is_empty() const {
        return (count_ == 0U);
    }
    
    bool is_full() const {
        return (count_ == capacity_);
    }
    
private:
    std::vector<T> buffer_;
    std::uint32_t head_;
    std::uint32_t tail_;
    std::uint32_t count_;
    std::uint32_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
