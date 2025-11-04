#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <utility>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : storage_(capacity),
          capacity_(capacity),
          head_(static_cast<std::size_t>(0U)),
          tail_(static_cast<std::size_t>(0U)),
          size_(static_cast<std::size_t>(0U)) {
        if (((capacity_) == static_cast<std::size_t>(0U))) {
            throw std::invalid_argument("capacity must be > 0");
        }
    }

    T read() {
        if (((size_) == static_cast<std::size_t>(0U))) {
            throw std::domain_error("empty buffer");
        } else {
            T value = std::move(storage_[head_]);
            head_ = next_index(head_);
            size_ = (size_ - static_cast<std::size_t>(1U));
            return value;
        }
    }

    void write(const T& value) {
        if (((size_) == (capacity_))) {
            throw std::domain_error("full buffer");
        } else {
            storage_[tail_] = value;
            tail_ = next_index(tail_);
            size_ = (size_ + static_cast<std::size_t>(1U));
        }
    }

    void write(T&& value) {
        if (((size_) == (capacity_))) {
            throw std::domain_error("full buffer");
        } else {
            storage_[tail_] = std::move(value);
            tail_ = next_index(tail_);
            size_ = (size_ + static_cast<std::size_t>(1U));
        }
    }

    void overwrite(const T& value) {
        storage_[tail_] = value;
        if (((size_) == (capacity_))) {
            tail_ = next_index(tail_);
            head_ = next_index(head_);
            // size_ remains unchanged at capacity_
        } else {
            tail_ = next_index(tail_);
            size_ = (size_ + static_cast<std::size_t>(1U));
        }
    }

    void overwrite(T&& value) {
        storage_[tail_] = std::move(value);
        if (((size_) == (capacity_))) {
            tail_ = next_index(tail_);
            head_ = next_index(head_);
            // size_ remains unchanged at capacity_
        } else {
            tail_ = next_index(tail_);
            size_ = (size_ + static_cast<std::size_t>(1U));
        }
    }

    void clear() noexcept {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        size_ = static_cast<std::size_t>(0U);
    }

private:
    std::size_t next_index(std::size_t i) const noexcept {
        return (((i + static_cast<std::size_t>(1U)) % (capacity_)));
    }

    std::vector<T> storage_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
