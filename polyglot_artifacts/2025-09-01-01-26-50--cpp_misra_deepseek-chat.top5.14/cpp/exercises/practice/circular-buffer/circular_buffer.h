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
        : buffer_(capacity), head_(0), tail_(0), count_(0), capacity_(capacity) {
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        --count_;
        return value;
    }

    void write(const T& data) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = data;
        tail_ = (tail_ + 1) % capacity_;
        ++count_;
    }

    void overwrite(const T& data) {
        if (is_full()) {
            // Write the new data at the current tail
            buffer_[tail_] = data;
            // Move tail forward
            tail_ = (tail_ + 1) % capacity_;
            // Update head to point to the new oldest element
            head_ = tail_;
        } else {
            write(data);
        }
    }

    void clear() {
        head_ = 0;
        tail_ = 0;
        count_ = 0;
    }

    bool is_empty() const {
        return (count_ == 0);
    }

    bool is_full() const {
        return (count_ == capacity_);
    }

    std::size_t size() const {
        return count_;
    }

private:
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
    std::size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
