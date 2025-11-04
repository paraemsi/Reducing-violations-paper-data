#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <utility>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : data_(capacity) {}

    // Remove and return the oldest element.
    // Throws std::domain_error if the buffer is empty.
    T read() {
        if (size_ == 0) {
            throw std::domain_error("empty buffer");
        }
        T value = data_[head_];
        head_ = (head_ + 1) % data_.size();
        --size_;
        return value;
    }

    // Append an element at the end.
    // Throws std::domain_error if the buffer is full.
    void write(const T& value) {
        if (data_.empty() || size_ == data_.size()) {
            throw std::domain_error("full buffer");
        }
        data_[tail_] = value;
        tail_ = (tail_ + 1) % data_.size();
        ++size_;
    }

    // Rvalue overload to support move-only types.
    void write(T&& value) {
        if (data_.empty() || size_ == data_.size()) {
            throw std::domain_error("full buffer");
        }
        data_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % data_.size();
        ++size_;
    }

    // Append an element at the end, overwriting the oldest if full.
    void overwrite(const T& value) {
        if (data_.empty()) {
            return; // zero-capacity buffer: ignore writes
        }
        if (size_ < data_.size()) {
            data_[tail_] = value;
            tail_ = (tail_ + 1) % data_.size();
            ++size_;
        } else {
            // Buffer is full: write at tail and drop the oldest by advancing head.
            data_[tail_] = value;
            tail_ = (tail_ + 1) % data_.size();
            head_ = (head_ + 1) % data_.size();
            // size_ remains at capacity
        }
    }

    // Rvalue overload to support move-only types.
    void overwrite(T&& value) {
        if (data_.empty()) {
            return; // zero-capacity buffer: ignore writes
        }
        if (size_ < data_.size()) {
            data_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % data_.size();
            ++size_;
        } else {
            // Buffer is full: write at tail and drop the oldest by advancing head.
            data_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % data_.size();
            head_ = (head_ + 1) % data_.size();
            // size_ remains at capacity
        }
    }

    // Remove all elements.
    void clear() noexcept {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

private:
    std::vector<T> data_;
    std::size_t head_{0}; // index of oldest element
    std::size_t tail_{0}; // index for next write when not full
    std::size_t size_{0}; // number of valid elements
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
