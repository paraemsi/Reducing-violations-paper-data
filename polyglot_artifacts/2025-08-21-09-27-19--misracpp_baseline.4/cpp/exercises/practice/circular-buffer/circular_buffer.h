#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity), capacity_(capacity), head_(0), tail_(0), size_(0) {
        if (capacity == 0) {
            throw std::domain_error("Circular buffer of zero capacity is invalid");
        }
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void overwrite(const T& value) {
        if (full()) {
            buffer_[tail_] = value;
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;
        } else {
            write(value);
        }
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

    void clear() {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == capacity_;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

} // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
