#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

#ifndef CIRCULAR_BUFFER_NODISCARD
#  if defined(__has_cpp_attribute)
#    if __has_cpp_attribute(nodiscard)
#      define CIRCULAR_BUFFER_NODISCARD [[nodiscard]]
#    else
#      define CIRCULAR_BUFFER_NODISCARD
#    endif
#  else
#    define CIRCULAR_BUFFER_NODISCARD
#  endif
#endif

namespace circular_buffer {

template <typename T>
class circular_buffer final {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(static_cast<std::size_t>(0)),
          tail_(static_cast<std::size_t>(0)),
          count_(static_cast<std::size_t>(0)) {
        if ((capacity == static_cast<std::size_t>(0))) {
            throw std::invalid_argument("capacity must be greater than 0");
        } else {
            // ok
        }
    }

    void write(const T& value) {
        if ((full())) {
            throw std::domain_error("buffer full");
        } else {
            buffer_.at(tail_) = value;
            advance_index(tail_);
            count_ = (count_ + static_cast<std::size_t>(1));
        }
    }

    void overwrite(const T& value) {
        if ((full())) {
            buffer_.at(tail_) = value;
            advance_index(tail_);
            advance_index(head_);
            // count_ unchanged when overwriting a full buffer
        } else {
            write(value);
        }
    }

    T read() {
        if ((empty())) {
            throw std::domain_error("buffer empty");
        } else {
            T value = buffer_.at(head_);
            advance_index(head_);
            count_ = (count_ - static_cast<std::size_t>(1));
            return value;
        }
    }

    void clear() noexcept {
        head_ = static_cast<std::size_t>(0);
        tail_ = static_cast<std::size_t>(0);
        count_ = static_cast<std::size_t>(0);
    }

    CIRCULAR_BUFFER_NODISCARD bool empty() const noexcept {
        return (count_ == static_cast<std::size_t>(0));
    }

    CIRCULAR_BUFFER_NODISCARD bool full() const noexcept {
        return (count_ == capacity_);
    }

    CIRCULAR_BUFFER_NODISCARD std::size_t capacity() const noexcept {
        return capacity_;
    }

    CIRCULAR_BUFFER_NODISCARD std::size_t size() const noexcept {
        return count_;
    }

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;

    void advance_index(std::size_t& idx) noexcept {
        idx = (idx + static_cast<std::size_t>(1));
        if ((idx == capacity_)) {
            idx = static_cast<std::size_t>(0);
        } else {
            // no wrap
        }
    }
};
 
}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
