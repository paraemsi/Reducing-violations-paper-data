#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <utility>
#include <vector>
#include <stdexcept>

namespace circular_buffer {

struct buffer_empty_exception : std::domain_error {
    buffer_empty_exception() : std::domain_error("circular buffer is empty") {}
};

struct buffer_full_exception : std::domain_error {
    buffer_full_exception() : std::domain_error("circular buffer is full") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_{capacity}, buffer_(capacity), head_{0}, tail_{0}, size_{0} {
        if (capacity_ == 0) {
            throw std::invalid_argument("circular buffer capacity must be > 0");
        }
    }

    T read() {
        if (empty()) {
            throw buffer_empty_exception{};
        }
        T value = std::move(buffer_[head_]);
        head_ = increment(head_);
        --size_;
        return value;
    }

    void write(T item) {
        if (full()) {
            throw buffer_full_exception{};
        }
        buffer_[tail_] = std::move(item);
        tail_ = increment(tail_);
        ++size_;
    }


    void overwrite(T item) {
        if (full()) {
            buffer_[tail_] = std::move(item);
            tail_ = increment(tail_);
            head_ = increment(head_); // drop the oldest
            // size_ remains at capacity_
        } else {
            write(std::move(item));
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

    std::size_t increment(std::size_t index) const noexcept {
        // capacity_ > 0 guaranteed by constructor
        ++index;
        if (index == capacity_) {
            index = 0;
        }
        return index;
    }

    std::size_t capacity_;
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
