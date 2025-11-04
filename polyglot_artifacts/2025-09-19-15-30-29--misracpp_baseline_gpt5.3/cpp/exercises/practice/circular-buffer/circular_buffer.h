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
        : buf_(capacity), head_(0), tail_(0), size_(0), capacity_(capacity) {}

    T read() {
        if (empty()) {
            throw std::domain_error("empty buffer");
        }
        T value = std::move(buf_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (capacity_ == 0 || full()) {
            throw std::domain_error("full buffer");
        }
        buf_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void write(T&& value) {
        if (capacity_ == 0 || full()) {
            throw std::domain_error("full buffer");
        }
        buf_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return; // nothing to store
        }
        if (full()) {
            // Write at tail (next insertion point), then advance both pointers
            buf_[tail_] = value;
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) {
            return; // nothing to store
        }
        if (full()) {
            // Write at tail (next insertion point), then advance both pointers
            buf_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;
        } else {
            write(std::move(value));
        }
    }

    void clear() noexcept {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

private:
    bool full() const noexcept { return size_ == capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    std::vector<T> buf_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
    std::size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
