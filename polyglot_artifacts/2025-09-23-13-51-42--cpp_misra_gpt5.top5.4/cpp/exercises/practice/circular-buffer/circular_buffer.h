#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <utility>

namespace circular_buffer {

struct buffer_empty : public std::domain_error {
    buffer_empty() : std::domain_error("buffer is empty") {}
};

struct buffer_full : public std::domain_error {
    buffer_full() : std::domain_error("buffer is full") {}
};

template <typename T>
class circular_buffer {
public:
    using size_type = std::size_t;

    explicit circular_buffer(size_type capacity)
        : buf_(capacity),
          capacity_(capacity),
          head_(static_cast<size_type>(0)),
          tail_(static_cast<size_type>(0)),
          size_(static_cast<size_type>(0)) {
        if ((capacity) == (static_cast<size_type>(0))) {
            throw std::invalid_argument("capacity must be greater than 0");
        } else {
            // no-op
        }
    }

    void clear() noexcept {
        head_ = static_cast<size_type>(0);
        tail_ = static_cast<size_type>(0);
        size_ = static_cast<size_type>(0);
    }

    bool empty() const noexcept {
        return (size_) == (static_cast<size_type>(0));
    }

    bool full() const noexcept {
        return (size_) == (capacity_);
    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    size_type size() const noexcept {
        return size_;
    }

    void write(const T& value) {
        if ((size_) == (capacity_)) {
            throw buffer_full{};
        } else {
            buf_[tail_] = value;
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

    void write(T&& value) {
        if ((size_) == (capacity_)) {
            throw buffer_full{};
        } else {
            buf_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

    T read() {
        if ((size_) == (static_cast<size_type>(0))) {
            throw buffer_empty{};
        } else {
            T value = std::move(buf_[head_]);
            head_ = ((head_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ - static_cast<size_type>(1));
            return value;
        }
    }

    void overwrite(const T& value) {
        if ((size_) == (capacity_)) {
            // Buffer is full: overwrite the oldest element and advance both head and tail.
            buf_[tail_] = value;
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            head_ = ((head_ + static_cast<size_type>(1)) % capacity_);
        } else {
            buf_[tail_] = value;
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

    void overwrite(T&& value) {
        if ((size_) == (capacity_)) {
            // Buffer is full: overwrite the oldest element and advance both head and tail.
            buf_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            head_ = ((head_ + static_cast<size_type>(1)) % capacity_);
        } else {
            buf_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

private:
    std::vector<T> buf_;
    size_type capacity_;
    size_type head_;
    size_type tail_;
    size_type size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
