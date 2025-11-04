#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

struct buffer_empty : public std::domain_error {
    buffer_empty() : std::domain_error("circular buffer is empty") {}
};

struct buffer_full : public std::domain_error {
    buffer_full() : std::domain_error("circular buffer is full") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          size_(0) {}

    T read() {
        if (size_ == 0) {
            throw buffer_empty{};
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (size_ == capacity_) {
            throw buffer_full{};
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void write(T&& value) {
        if (size_ == capacity_) {
            throw buffer_full{};
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
            buffer_[tail_] = value;
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
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
        head_ = tail_ = 0;
        size_ = 0;
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
