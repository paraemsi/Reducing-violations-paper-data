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
        : buffer_(capacity), capacity_(capacity), head_(0), tail_(0), size_(0) {}

    T read() {
        if (empty()) {
            throw std::domain_error("Cannot read from empty buffer");
        }
        T value = std::move(buffer_[head_]);
        head_ = next_index(head_);
        --size_;
        return value;
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("Cannot write to full buffer");
        }
        buffer_[tail_] = value;
        tail_ = next_index(tail_);
        ++size_;
    }

    void write(T&& value) {
        if (full()) {
            throw std::domain_error("Cannot write to full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = next_index(tail_);
        ++size_;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return;
        }
        if (full()) {
            buffer_[tail_] = value;
            tail_ = next_index(tail_);
            head_ = next_index(head_);
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) {
            return;
        }
        if (full()) {
            buffer_[tail_] = std::move(value);
            tail_ = next_index(tail_);
            head_ = next_index(head_);
        } else {
            write(std::move(value));
        }
    }

    void clear() {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    bool empty() const noexcept { return size_ == 0; }
    bool full() const noexcept { return size_ == capacity_; }
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }

private:
    std::size_t next_index(std::size_t idx) const noexcept { return capacity_ == 0 ? 0 : (idx + 1) % capacity_; }
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
