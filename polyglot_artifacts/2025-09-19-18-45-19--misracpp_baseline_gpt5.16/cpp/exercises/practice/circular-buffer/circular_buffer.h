#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <optional>
#include <vector>

namespace circular_buffer {

struct buffer_empty_exception : std::domain_error {
    buffer_empty_exception() : std::domain_error("circular_buffer: empty") {}
};
struct buffer_full_exception : std::domain_error {
    buffer_full_exception() : std::domain_error("circular_buffer: full") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity), capacity_(capacity), head_(0), tail_(0), size_(0) {
        if (capacity_ == 0) {
            throw std::invalid_argument("circular_buffer capacity must be > 0");
        }
    }

    T read() {
        if (empty()) {
            throw buffer_empty_exception{};
        }
        T value = std::move(*(buffer_[head_]));
        buffer_[head_].reset();
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (full()) {
            throw buffer_full_exception{};
        }
        buffer_[tail_].emplace(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void write(T&& value) {
        if (full()) {
            throw buffer_full_exception{};
        }
        buffer_[tail_].emplace(std::move(value));
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void overwrite(const T& value) {
        if (full()) {
            buffer_[tail_].emplace(value);
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
        if (full()) {
            buffer_[tail_].emplace(std::move(value));
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;
        } else {
            write(std::move(value));
        }
    }

    void clear() {
        for (auto& slot : buffer_) {
            slot.reset();
        }
        head_ = tail_ = size_ = 0;
    }

private:
    bool empty() const noexcept { return size_ == 0; }
    bool full() const noexcept { return size_ == capacity_; }

    std::vector<std::optional<T>> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
