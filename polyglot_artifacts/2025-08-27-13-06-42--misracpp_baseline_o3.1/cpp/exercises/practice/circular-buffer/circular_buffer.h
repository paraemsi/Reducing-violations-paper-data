#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace circular_buffer {

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(std::size_t capacity)
        : buffer_(capacity), head_(0), tail_(0), size_(0), capacity_(capacity) {
        if (capacity_ == 0) {
            throw std::domain_error("zero capacity");
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("empty buffer");
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    // rvalue-reference overload enables efficient moves (e.g., std::string)
    void write(T&& value) {
        if (full()) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void overwrite(const T& value) {
        if (full()) {
            buffer_[tail_] = std::move(value);
            head_ = (head_ + 1) % capacity_;
            tail_ = (tail_ + 1) % capacity_;
        } else {
            write(value);
        }
    }

    void clear() {
        head_ = tail_ = size_ = 0;
    }

    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == capacity_; }

private:
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
    std::size_t capacity_;
};

template <typename T>
using circular_buffer = CircularBuffer<T>;

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
