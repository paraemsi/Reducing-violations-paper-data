#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          head_(0),
          tail_(0),
          size_(0),
          capacity_(capacity) {}

    T read() {
        if (size_ == 0) {
            throw std::domain_error("Empty buffer");
        }
        T value = std::move(*(buffer_[head_]));
        buffer_[head_].reset();
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (capacity_ == 0 || size_ == capacity_) {
            throw std::domain_error("Full buffer");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void write(T&& value) {
        if (capacity_ == 0 || size_ == capacity_) {
            throw std::domain_error("Full buffer");
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return;
        }
        if (size_ == capacity_) {
            // Drop oldest
            head_ = (head_ + 1) % capacity_;
            // size_ remains at capacity
        } else {
            ++size_;
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) {
            return;
        }
        if (size_ == capacity_) {
            // Drop oldest
            head_ = (head_ + 1) % capacity_;
            // size_ remains at capacity
        } else {
            ++size_;
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
    }

    void clear() {
        for (auto& slot : buffer_) {
            slot.reset();
        }
        head_ = tail_ = 0;
        size_ = 0;
    }

private:
    std::vector<std::optional<T>> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
    std::size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
