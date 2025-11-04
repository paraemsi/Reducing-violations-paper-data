#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity), head_(0), tail_(0), size_(0) {
        if (capacity == 0) {
            throw std::invalid_argument("capacity must be > 0");
        }
    }

    // Query functions
    std::size_t capacity() const { return buffer_.size(); }
    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == capacity(); }

    // Remove and return the oldest element.
    // Throws std::domain_error if the buffer is empty.
    T read() {
        if (empty()) {
            throw std::domain_error("cannot read from empty buffer");
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity();
        --size_;
        return value;
    }

    // Write a new element. Throws std::domain_error if the buffer is full.
    void write(const T& value) {
        if (full()) {
            throw std::domain_error("cannot write to full buffer");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity();
        ++size_;
    }

    // Move overload for write.
    void write(T&& value) {
        if (full()) {
            throw std::domain_error("cannot write to full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity();
        ++size_;
    }

    // Overwrite the oldest element if the buffer is full; otherwise behaves like write.
    void overwrite(const T& value) {
        if (full()) {
            buffer_[tail_] = value;
            tail_ = (tail_ + 1) % capacity();
            head_ = (head_ + 1) % capacity();
            // size_ remains at capacity
        } else {
            write(value);
        }
    }

    // Move overload for overwrite.
    void overwrite(T&& value) {
        if (full()) {
            buffer_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % capacity();
            head_ = (head_ + 1) % capacity();
            // size_ remains at capacity
        } else {
            write(std::move(value));
        }
    }

    // Remove all elements.
    void clear() {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

private:

    std::vector<T> buffer_;
    std::size_t head_;  // index of next read (oldest)
    std::size_t tail_;  // index of next write
    std::size_t size_;  // number of elements currently stored
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
