#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <optional>
#include <utility>
#include <vector>

namespace circular_buffer {
template <typename T>
class circular_buffer {
public:
    using size_type = std::size_t;

    explicit circular_buffer(size_type capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(static_cast<size_type>(0)),
          tail_(static_cast<size_type>(0)),
          size_(static_cast<size_type>(0)) {
    }

    circular_buffer(const circular_buffer&) = default;
    circular_buffer(circular_buffer&&) = default;
    circular_buffer& operator=(const circular_buffer&) = default;
    circular_buffer& operator=(circular_buffer&&) = default;
    ~circular_buffer() = default;

    void clear() noexcept {
        for (std::optional<T>& slot : buffer_) {
            slot.reset();
        }
        head_ = static_cast<size_type>(0);
        tail_ = static_cast<size_type>(0);
        size_ = static_cast<size_type>(0);
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("circular buffer is full");
        } else {
            if ((capacity_) == static_cast<size_type>(0)) {
                throw std::domain_error("circular buffer is full");
            }
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

    void write(T&& value) {
        if (full()) {
            throw std::domain_error("circular buffer is full");
        } else {
            if ((capacity_) == static_cast<size_type>(0)) {
                throw std::domain_error("circular buffer is full");
            }
            buffer_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("circular buffer is empty");
        } else {
            T value = std::move(*(buffer_[head_]));
            buffer_[head_].reset();
            head_ = ((head_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ - static_cast<size_type>(1));
            return value;
        }
    }

    void overwrite(const T& value) noexcept {
        if ((capacity_) == static_cast<size_type>(0)) {
            return;
        }
        if (full()) {
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            head_ = ((head_ + static_cast<size_type>(1)) % capacity_);
        } else {
            buffer_[tail_] = value;
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

    void overwrite(T&& value) noexcept {
        if ((capacity_) == static_cast<size_type>(0)) {
            return;
        }
        if (full()) {
            buffer_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            head_ = ((head_ + static_cast<size_type>(1)) % capacity_);
        } else {
            buffer_[tail_] = std::move(value);
            tail_ = ((tail_ + static_cast<size_type>(1)) % capacity_);
            size_ = (size_ + static_cast<size_type>(1));
        }
    }

    [[nodiscard]] size_type capacity() const noexcept {
        return (capacity_);
    }

    [[nodiscard]] size_type size() const noexcept {
        return (size_);
    }

    [[nodiscard]] bool empty() const noexcept {
        return (size_) == static_cast<size_type>(0);
    }

    [[nodiscard]] bool full() const noexcept {
        return (size_) == (capacity_);
    }

private:
    std::vector<std::optional<T>> buffer_;
    size_type capacity_;
    size_type head_;
    size_type tail_;
    size_type size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
