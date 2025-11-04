#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <vector>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::uint32_t capacity)
        : buffer_(),
          head_(0U),
          tail_(0U),
          count_(0U) {
        if (capacity == 0U) {
            throw std::domain_error("capacity must be greater than zero");
        }

        /* Allocate storage only after validating capacity */
        buffer_.resize(static_cast<std::size_t>(capacity));
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("buffer is full");
        } else {
            buffer_[tail_] = value;
            tail_ = static_cast<std::uint32_t>(
                (tail_ + 1U) %
                static_cast<std::uint32_t>(buffer_.size()));
            ++count_;
        }
    }

    void overwrite(const T& value) {
        if (full()) {
            buffer_[tail_] = value;
            tail_ = static_cast<std::uint32_t>(
                (tail_ + 1U) %
                static_cast<std::uint32_t>(buffer_.size()));
            head_ = tail_;
        } else {
            write(value);
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("buffer is empty");
        } else {
            T value = buffer_[head_];
            head_ = static_cast<std::uint32_t>(
                (head_ + 1U) %
                static_cast<std::uint32_t>(buffer_.size()));
            --count_;
            return value;
        }
    }

    void clear() noexcept {
        head_ = 0U;
        tail_ = 0U;
        count_ = 0U;
    }

    [[nodiscard]] bool empty() const noexcept {
        return (count_ == 0U);
    }

    [[nodiscard]] bool full() const noexcept {
        return (count_ == static_cast<std::uint32_t>(buffer_.size()));
    }

    [[nodiscard]] std::uint32_t size() const noexcept {
        return count_;
    }

    [[nodiscard]] std::uint32_t capacity() const noexcept {
        return static_cast<std::uint32_t>(buffer_.size());
    }

private:
    std::vector<T> buffer_;
    std::uint32_t head_;
    std::uint32_t tail_;
    std::uint32_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
