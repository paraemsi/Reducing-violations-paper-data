#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

class buffer_empty_exception final : public std::domain_error {
public:
    buffer_empty_exception() : std::domain_error("circular_buffer: read from empty buffer") {}
};

class buffer_full_exception final : public std::domain_error {
public:
    buffer_full_exception() : std::domain_error("circular_buffer: write to full buffer") {}
};

template <typename T>
class circular_buffer final {
public:
    using size_type = std::size_t;

    explicit circular_buffer(size_type capacity)
        : capacity_{capacity},
          buffer_(capacity),
          head_{static_cast<size_type>(0U)},
          size_{static_cast<size_type>(0U)} {
        if ((capacity_ == static_cast<size_type>(0U))) {
            throw std::invalid_argument("capacity must be > 0");
        }
    }

    void clear() noexcept {
        head_ = static_cast<size_type>(0U);
        size_ = static_cast<size_type>(0U);
    }

    bool is_empty() const noexcept {
        return (size_ == static_cast<size_type>(0U));
    }

    bool is_full() const noexcept {
        return (size_ == capacity_);
    }

    size_type size() const noexcept {
        return size_;
    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    T read() {
        if ((is_empty())) {
            throw buffer_empty_exception{};
        }

        const size_type idx = head_;
        head_ = next_index(head_);
        size_ = (size_ - static_cast<size_type>(1U));
        return buffer_[idx];
    }

    void write(T value) {
        if ((is_full())) {
            throw buffer_full_exception{};
        }

        const size_type pos = write_index();
        buffer_[pos] = std::move(value);
        size_ = (size_ + static_cast<size_type>(1U));
    }

    void overwrite(T value) {
        if ((is_full())) {
            buffer_[head_] = std::move(value);
            head_ = next_index(head_);
        } else {
            write(std::move(value));
        }
    }

private:
    size_type next_index(size_type idx) const noexcept {
        return ((idx + static_cast<size_type>(1U)) % capacity_);
    }

    size_type write_index() const noexcept {
        const size_type idx = (head_ + size_);
        return (idx % capacity_);
    }

    size_type capacity_;
    std::vector<T> buffer_;
    size_type head_;
    size_type size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
