#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

struct buffer_empty final : public std::exception {
    const char* what() const noexcept override {
        return "circular buffer is empty";
    }
};

struct buffer_full final : public std::exception {
    const char* what() const noexcept override {
        return "circular buffer is full";
    }
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : storage_(capacity),
          capacity_(capacity),
          head_(static_cast<std::size_t>(0)),
          tail_(static_cast<std::size_t>(0)),
          size_(static_cast<std::size_t>(0)) {}

    T read() {
        if ((size_ == static_cast<std::size_t>(0))) {
            throw std::domain_error("circular buffer is empty");
        } else {
            T value = std::move(storage_[tail_]);
            if ((capacity_ != static_cast<std::size_t>(0))) {
                tail_ = ((tail_ + static_cast<std::size_t>(1)) % capacity_);
            }
            size_ = (size_ - static_cast<std::size_t>(1));
            return value;
        }
    }

    void write(const T& value) {
        if ((capacity_ == static_cast<std::size_t>(0))) {
            throw std::domain_error("circular buffer is full");
        } else {
            if ((size_ == capacity_)) {
                throw std::domain_error("circular buffer is full");
            } else {
                storage_[head_] = value;
                head_ = ((head_ + static_cast<std::size_t>(1)) % capacity_);
                size_ = (size_ + static_cast<std::size_t>(1));
            }
        }
    }

    void write(T&& value) {
        if ((capacity_ == static_cast<std::size_t>(0))) {
            throw std::domain_error("circular buffer is full");
        } else {
            if ((size_ == capacity_)) {
                throw std::domain_error("circular buffer is full");
            } else {
                storage_[head_] = std::move(value);
                head_ = ((head_ + static_cast<std::size_t>(1)) % capacity_);
                size_ = (size_ + static_cast<std::size_t>(1));
            }
        }
    }

    void overwrite(const T& value) {
        if ((capacity_ == static_cast<std::size_t>(0))) {
            // No storage available; behave as a no-op to avoid modulo by zero.
            return;
        } else {
            if ((size_ == capacity_)) {
                // Drop the oldest element.
                tail_ = ((tail_ + static_cast<std::size_t>(1)) % capacity_);
                // size_ remains at capacity_
            } else {
                size_ = (size_ + static_cast<std::size_t>(1));
            }
            storage_[head_] = value;
            head_ = ((head_ + static_cast<std::size_t>(1)) % capacity_);
        }
    }

    void clear() noexcept {
        head_ = static_cast<std::size_t>(0);
        tail_ = static_cast<std::size_t>(0);
        size_ = static_cast<std::size_t>(0);
    }

private:
    std::vector<T> storage_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
