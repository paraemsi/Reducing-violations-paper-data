#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

struct buffer_empty : std::domain_error {
    buffer_empty() : std::domain_error{"empty buffer"} {}
};

struct buffer_full : std::domain_error {
    buffer_full() : std::domain_error{"full buffer"} {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_{capacity},
          buf_(capacity_),
          head_{0},
          tail_{0},
          full_{false} {
        if (capacity_ == 0) {
            throw std::invalid_argument{"capacity must be > 0"};
        }
    }

    // Remove and return the oldest element.
    T read() {
        if (is_empty()) {
            throw std::domain_error{"empty buffer"};
        }

        std::optional<T> &slot = buf_[tail_];
        T value = std::move(*slot);
        slot.reset();

        advance(tail_);
        full_ = false;
        return value;
    }

    // Add an element if space is available; otherwise throw.
    void write(const T& item) {
        if (full_) {
            throw std::domain_error{"full buffer"};
        }
        buf_[head_] = item;
        advance(head_);
        if (head_ == tail_) {
            full_ = true;
        }
    }

    // Overwrite the oldest element when buffer is full; otherwise behaves like write.
    void overwrite(const T& item) {
        if (full_) {
            // Drop oldest
            advance(tail_);
            // head_ already points to slot to be written (same as tail_ before advance)
        }
        buf_[head_] = item;
        advance(head_);
        if (head_ == tail_) {
            full_ = true;
        }
    }

    // Remove all elements.
    void clear() {
        buf_.assign(capacity_, std::nullopt);
        head_ = tail_ = 0;
        full_ = false;
    }

    bool is_empty() const {
        return (!full_ && head_ == tail_);
    }

    bool is_full() const {
        return full_;
    }

private:
    void advance(std::size_t &index) {
        index = (index + 1) % capacity_;
    }

    std::size_t capacity_;
    std::vector<std::optional<T>> buf_;
    std::size_t head_; // next write position
    std::size_t tail_; // next read position
    bool full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
