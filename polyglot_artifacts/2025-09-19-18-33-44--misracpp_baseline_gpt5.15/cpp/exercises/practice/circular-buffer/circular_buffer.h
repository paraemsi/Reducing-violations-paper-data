#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

// Generic fixed-capacity circular buffer.
//
// Operations:
// - read(): removes and returns the oldest element; throws std::domain_error if empty.
// - write(): appends a new element; throws std::domain_error if full.
// - overwrite(): appends a new element; if full, overwrites the oldest element.
// - clear(): removes all elements.
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity), head_(0), tail_(0), size_(0), capacity_(capacity) {}

    T read() {
        if (empty()) {
            throw std::domain_error("empty buffer");
        }
        T value = std::move(buffer_[head_]);
        head_ = next_index(head_);
        --size_;
        return value;
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = value;
        tail_ = next_index(tail_);
        ++size_;
    }

    void write(T&& value) {
        if (full()) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = next_index(tail_);
        ++size_;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return; // No storage available; nothing to overwrite.
        }
        if (!full()) {
            write(value);
            return;
        }
        // Buffer is full: replace the oldest element and advance head.
        buffer_[head_] = value;
        head_ = next_index(head_);
        tail_ = head_; // keep invariant tail == head when full
        // size_ remains at capacity_
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) {
            return; // No storage available; nothing to overwrite.
        }
        if (!full()) {
            write(std::move(value));
            return;
        }
        buffer_[head_] = std::move(value);
        head_ = next_index(head_);
        tail_ = head_;
        // size_ remains at capacity_
    }

    void clear() noexcept {
        head_ = tail_ = 0;
        size_ = 0;
    }

private:
    bool empty() const noexcept { return size_ == 0; }
    bool full() const noexcept { return size_ == capacity_; }

    std::size_t next_index(std::size_t i) const noexcept {
        return capacity_ == 0 ? 0 : (i + 1) % capacity_;
    }

    std::vector<T> buffer_;
    std::size_t head_;     // index of the oldest element
    std::size_t tail_;     // index of the next write position (after newest)
    std::size_t size_;     // number of elements currently stored
    std::size_t capacity_; // fixed capacity of the buffer
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
