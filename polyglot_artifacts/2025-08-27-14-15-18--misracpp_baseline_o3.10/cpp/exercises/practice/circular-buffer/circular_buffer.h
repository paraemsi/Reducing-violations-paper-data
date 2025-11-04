#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          full_(false) {
        if (capacity == 0) {
            throw std::invalid_argument("circular buffer capacity must be greater than 0");
        }
    }

    T read() {
        if (empty()) {
            throw buffer_empty{};
        }
        T value = std::move(buffer_[head_]);
        advance_head();
        return value;
    }

    void write(const T& value) {
        if (full_) {
            throw buffer_full{};
        }
        buffer_[tail_] = value;
        advance_tail();
    }

    // rvalue overload for move-only and movable types
    void write(T&& value) {
        if (full_) {
            throw buffer_full{};
        }
        buffer_[tail_] = std::move(value);
        advance_tail();
    }

    void overwrite(const T& value) {
        if (full_) {
            buffer_[head_] = value;
            advance_head();
            advance_tail();
        } else {
            write(value);
        }
    }

    // rvalue overload for overwrite
    void overwrite(T&& value) {
        if (full_) {
            buffer_[head_] = std::move(value);
            advance_head();
            advance_tail();
        } else {
            write(std::move(value));
        }
    }

    void clear() noexcept {
        head_ = 0;
        tail_ = 0;
        full_ = false;
    }

    struct buffer_empty : std::domain_error {
        buffer_empty() : std::domain_error("circular buffer is empty") {}
    };

    struct buffer_full : std::domain_error {
        buffer_full() : std::domain_error("circular buffer is full") {}
    };

private:
    bool empty() const noexcept { return (!full_ && head_ == tail_); }

    // move head forward and mark buffer as not full
    void advance_head() noexcept {
        head_ = (head_ + 1) % capacity_;
        full_ = false;
    }

    void advance_tail() noexcept {
        tail_ = (tail_ + 1) % capacity_;
        if (tail_ == head_) {
            full_ = true;
        }
    }

    std::vector<T> buffer_;
    std::size_t    capacity_;
    std::size_t    head_;
    std::size_t    tail_;
    bool           full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
