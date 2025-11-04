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
        : buffer_(capacity), head_(0), tail_(0), size_(0), capacity_(capacity) {}

    T read() {
        if (size_ == 0) {
            throw std::domain_error("empty buffer");
        }
        const std::size_t idx = head_;
        head_ = (head_ + 1) % capacity_;
        --size_;
        return std::move(buffer_[idx]);
    }

    void write(T value) {
        if (size_ == capacity_) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }


    void overwrite(T value) {
        if (capacity_ == 0) {
            return;
        }
        if (size_ == capacity_) {
            buffer_[tail_] = std::move(value);
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
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
    std::size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
