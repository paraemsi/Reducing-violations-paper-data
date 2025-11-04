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
        : buffer_(capacity), head_(0U), tail_(0U), count_(0U), capacity_(capacity) {
    }

    T read() {
        if (count_ == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1U) % capacity_;
        count_--;
        return value;
    }

    void write(const T& data) {
        if (count_ == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = data;
        tail_ = (tail_ + 1U) % capacity_;
        count_++;
    }

    void overwrite(const T& data) {
        if (count_ == capacity_) {
            // Buffer is full, overwrite the oldest element which is at head_
            buffer_[head_] = data;
            // Advance both pointers
            head_ = (head_ + 1U) % capacity_;
            tail_ = head_;
        } else {
            write(data);
        }
    }

    void clear() {
        head_ = 0U;
        tail_ = 0U;
        count_ = 0U;
    }

    std::uint32_t capacity() const {
        return capacity_;
    }

    std::uint32_t size() const {
        return count_;
    }

    bool empty() const {
        return (count_ == 0U);
    }

    bool full() const {
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
