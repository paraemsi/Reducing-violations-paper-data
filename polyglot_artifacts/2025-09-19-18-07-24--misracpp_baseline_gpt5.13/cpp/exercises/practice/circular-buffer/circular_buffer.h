#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {
// Exceptions derive from std::domain_error (tests catch std::domain_error)

struct empty_buffer_error : std::domain_error {
    empty_buffer_error() : std::domain_error("buffer is empty") {}
};

struct full_buffer_error : std::domain_error {
    full_buffer_error() : std::domain_error("buffer is full") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_(capacity),
          data_(capacity),
          head_(0),
          tail_(0),
          size_(0) {}

    // Write a value if space is available, otherwise throw.
    void write(const T& value) {
        if (size_ == capacity_) {
            throw full_buffer_error();
        }
        put_(value);
    }

    void write(T&& value) {
        if (size_ == capacity_) {
            throw full_buffer_error();
        }
        put_(std::move(value));
    }

    // Read and remove the oldest value, or throw if empty.
    T read() {
        if (size_ == 0) {
            throw empty_buffer_error();
        }
        T out = std::move(*(data_[head_]));
        data_[head_].reset();
        head_ = next_(head_);
        --size_;
        return out;
    }

    // Force a write: overwrite the oldest element if full.
    void overwrite(const T& value) {
        if (capacity_ == 0) return; // nothing to do
        if (size_ == capacity_) {
            data_[tail_] = std::unique_ptr<T>(new T(value));
            tail_ = next_(tail_);
            head_ = next_(head_); // dropped oldest
        } else {
            put_(value);
        }
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) return; // nothing to do
        if (size_ == capacity_) {
            data_[tail_] = std::unique_ptr<T>(new T(std::move(value)));
            tail_ = next_(tail_);
            head_ = next_(head_); // dropped oldest
        } else {
            put_(std::move(value));
        }
    }

    // Remove all elements.
    void clear() {
        for (auto& slot : data_) {
            slot.reset();
        }
        head_ = tail_ = size_ = 0;
    }

private:
    std::size_t next_(std::size_t i) const {
        // Not called when capacity_ == 0
        ++i;
        if (i == capacity_) i = 0;
        return i;
    }

    template <typename U>
    void put_(U&& value) {
        data_[tail_] = std::unique_ptr<T>(new T(std::forward<U>(value)));
        tail_ = next_(tail_);
        ++size_;
    }

    std::size_t capacity_;
    std::vector<std::unique_ptr<T>> data_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
