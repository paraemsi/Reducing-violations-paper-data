#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

// A fixed-capacity circular (ring) buffer.
// - write(): append an item; throws if buffer is full
// - overwrite(): append an item; overwrites the oldest when buffer is full
// - read(): remove and return the oldest item; throws if buffer is empty
// - clear(), empty(), full(), size(), capacity()
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(static_cast<std::size_t>(0U)),
          tail_(static_cast<std::size_t>(0U)),
          count_(static_cast<std::size_t>(0U)) {
        if ((capacity_ == static_cast<std::size_t>(0U))) {
            throw std::domain_error("capacity must be > 0");
        } else {
            // ok
        }
    }

    void clear() noexcept {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        count_ = static_cast<std::size_t>(0U);
    }

    bool empty() const noexcept {
        return (count_ == static_cast<std::size_t>(0U));
    }

    bool full() const noexcept {
        return (count_ == capacity_);
    }

    std::size_t size() const noexcept {
        return count_;
    }

    std::size_t capacity() const noexcept {
        return capacity_;
    }

    void write(const T& item) {
        if (full()) {
            throw std::domain_error("buffer is full");
        } else {
            buffer_[tail_] = item;
            tail_ = increment_(tail_);
            count_ = (count_ + static_cast<std::size_t>(1U));
        }
    }

    void overwrite(const T& item) {
        if (full()) {
            buffer_[tail_] = item;
            tail_ = increment_(tail_);
            head_ = increment_(head_);
            // count_ remains equal to capacity_
        } else {
            write(item);
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("buffer is empty");
        } else {
            T value = std::move(buffer_[head_]);
            head_ = increment_(head_);
            count_ = (count_ - static_cast<std::size_t>(1U));
            return value;
        }
    }

private:
    std::size_t increment_(std::size_t index) const noexcept {
        index = (index + static_cast<std::size_t>(1U));
        if ((index == capacity_)) {
            index = static_cast<std::size_t>(0U);
        } else {
            // no wrap
        }
        return index;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
