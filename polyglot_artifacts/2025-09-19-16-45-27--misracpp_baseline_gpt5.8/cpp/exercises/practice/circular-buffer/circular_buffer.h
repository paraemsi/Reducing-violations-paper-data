#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

class buffer_empty_exception : public std::domain_error {
public:
    buffer_empty_exception() : std::domain_error("empty buffer") {}
};

class buffer_full_exception : public std::domain_error {
public:
    buffer_full_exception() : std::domain_error("full buffer") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buf_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          size_(0) {}

    T read() {
        if (empty()) {
            throw buffer_empty_exception();
        }
        T value = std::move(buf_[head_]);
        advance(head_);
        --size_;
        return value;
    }

    void write(const T& value) {
        if (full()) {
            throw buffer_full_exception();
        }
        buf_[tail_] = value;
        advance(tail_);
        ++size_;
    }

    void write(T&& value) {
        if (full()) {
            throw buffer_full_exception();
        }
        buf_[tail_] = std::move(value);
        advance(tail_);
        ++size_;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return;
        }
        if (full()) {
            buf_[tail_] = value;
            advance(tail_);
            advance(head_);
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) {
            return;
        }
        if (full()) {
            buf_[tail_] = std::move(value);
            advance(tail_);
            advance(head_);
        } else {
            write(std::move(value));
        }
    }

    void clear() noexcept {
        head_ = tail_;
        size_ = 0;
    }

private:
    std::vector<T> buf_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;

    bool full() const noexcept { return size_ == capacity_; }
    bool empty() const noexcept { return size_ == 0; }
    void advance(std::size_t& idx) noexcept {
        if (capacity_ != 0) {
            idx = (idx + 1) % capacity_;
        }
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
