#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/**
 * Generic circular (ring) buffer.
 *
 * The buffer throws std::domain_error when:
 *  - write() is invoked while the buffer is full
 *  - read()  is invoked while the buffer is empty
 *
 * overwrite() never throws; if the buffer is full it drops the oldest element.
 */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          head_(0),
          tail_(0),
          max_size_(capacity),
          full_(false) {
        if (capacity == 0) {
            throw std::invalid_argument("capacity must be greater than 0");
        }
    }

    // Adds a new item to the buffer. Throws if the buffer is full.
    void write(const T& item) {
        if (full_) {
            throw std::domain_error("buffer full");
        }
        buffer_[tail_] = item;
        advance_tail();
    }

    // Adds a new item. If the buffer is full, the oldest item is overwritten.
    void overwrite(const T& item) {
        if (full_) {
            buffer_[head_] = item;          // overwrite oldest
            advance_head();                 // move head forward
        } else {
            write(item);
            return;                         // write() already advanced tail
        }
        // keep tail in sync with head advance
        advance_tail();
    }

    // Removes and returns the oldest item in the buffer.
    T read() {
        if (empty()) {
            throw std::domain_error("buffer empty");
        }
        T value = buffer_[head_];
        advance_head();
        full_ = false;
        return value;
    }

    // Clears the buffer contents.
    void clear() noexcept {
        head_ = tail_;
        full_ = false;
    }

    bool empty() const noexcept {
        return !full_ && (head_ == tail_);
    }

    bool full() const noexcept {
        return full_;
    }

    std::size_t size() const noexcept {
        if (full_) {
            return max_size_;
        }
        if (tail_ >= head_) {
            return tail_ - head_;
        }
        return max_size_ - head_ + tail_;
    }

    std::size_t capacity() const noexcept {
        return max_size_;
    }

private:
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t max_size_;
    bool full_;

    void advance_head() noexcept {
        head_ = (head_ + 1) % max_size_;
    }

    void advance_tail() noexcept {
        tail_ = (tail_ + 1) % max_size_;
        if (tail_ == head_) {
            full_ = true;
        }
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
