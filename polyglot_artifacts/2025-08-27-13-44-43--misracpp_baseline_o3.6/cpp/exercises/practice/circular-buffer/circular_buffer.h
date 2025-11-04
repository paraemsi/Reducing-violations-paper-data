#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <cstddef>
#include <stdexcept>

namespace circular_buffer {

// Circular buffer ---------------------------------------------------------

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
            throw std::invalid_argument("Circular buffer capacity must be greater than zero");
        }
    }

    // Remove and return the oldest element.
    T read() {
        if (empty()) {
            throw std::domain_error("Circular buffer is empty");
        }

        T value = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        full_ = false;
        return value;
    }

    // Add an element when space is available.
    void write(const T& item) {
        if (full_) {
            throw std::domain_error("Circular buffer is full");
        }

        buffer_[tail_] = item;
        advance_tail();
    }

    // Add an element, overwriting the oldest if the buffer is full.
    void overwrite(const T& item) {
        if (full_) {
            buffer_[head_] = item;
            advance_head();           // oldest element overwritten
        } else {
            buffer_[tail_] = item;
        }
        advance_tail();
    }

    // Remove all elements without changing capacity.
    void clear() noexcept {
        head_ = tail_;
        full_ = false;
    }

private:
    bool empty() const noexcept {
        return !full_ && (head_ == tail_);
    }

    void advance_head() noexcept {
        head_ = (head_ + 1) % capacity_;
    }

    void advance_tail() noexcept {
        tail_ = (tail_ + 1) % capacity_;
        if (tail_ == head_) {
            full_ = true;
        }
    }

    std::vector<T> buffer_;
    const std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    bool full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
