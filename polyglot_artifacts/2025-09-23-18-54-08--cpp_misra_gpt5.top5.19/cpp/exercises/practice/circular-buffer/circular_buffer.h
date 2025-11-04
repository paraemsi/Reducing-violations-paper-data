#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

struct buffer_empty : public std::domain_error {
    buffer_empty();
};

struct buffer_full : public std::domain_error {
    buffer_full();
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(std::size_t{0}),
          tail_(std::size_t{0}),
          size_(std::size_t{0}) {
        if ((capacity_ == std::size_t{0})) {
            throw std::invalid_argument("circular_buffer capacity must be greater than 0");
        }
    }

    T read() {
        if ((size_ == std::size_t{0})) {
            throw buffer_empty();
        } else {
            T value = buffer_[head_];
            head_ = ((head_ + std::size_t{1}) % capacity_);
            size_ = (size_ - std::size_t{1});
            return value;
        }
    }

    void write(const T& value) {
        if ((size_ == capacity_)) {
            throw buffer_full();
        } else {
            buffer_[tail_] = value;
            tail_ = ((tail_ + std::size_t{1}) % capacity_);
            size_ = (size_ + std::size_t{1});
        }
    }

    void overwrite(const T& value) {
        if ((size_ == capacity_)) {
            head_ = ((head_ + std::size_t{1}) % capacity_);
        } else {
            size_ = (size_ + std::size_t{1});
        }

        buffer_[tail_] = value;
        tail_ = ((tail_ + std::size_t{1}) % capacity_);
    }

    void clear() noexcept {
        head_ = std::size_t{0};
        tail_ = std::size_t{0};
        size_ = std::size_t{0};
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
