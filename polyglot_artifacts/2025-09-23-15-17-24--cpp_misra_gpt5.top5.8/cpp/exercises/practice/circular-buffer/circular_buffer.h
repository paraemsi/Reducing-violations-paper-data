#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

class buffer_empty_exception : public std::domain_error {
public:
    buffer_empty_exception() : std::domain_error("circular buffer is empty") {}
};

class buffer_full_exception : public std::domain_error {
public:
    buffer_full_exception() : std::domain_error("circular buffer is full") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : data_(capacity),
          capacity_(capacity),
          head_(static_cast<std::size_t>(0U)),
          size_(static_cast<std::size_t>(0U)) {
        if ((capacity_) == static_cast<std::size_t>(0U)) {
            throw std::invalid_argument("capacity must be greater than 0");
        }
    }

    T read() {
        if ((size_) == static_cast<std::size_t>(0U)) {
            throw buffer_empty_exception();
        }
        T value = data_[head_];
        head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        size_ = (size_ - static_cast<std::size_t>(1U));
        return value;
    }

    void write(const T& value) {
        if ((size_) == (capacity_)) {
            throw buffer_full_exception();
        }
        std::size_t idx = ((head_ + size_) % capacity_);
        data_[idx] = value;
        size_ = (size_ + static_cast<std::size_t>(1U));
    }

    void overwrite(const T& value) {
        if ((size_) == (capacity_)) {
            data_[head_] = value;
            head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
        } else {
            write(value);
        }
    }

    void clear() {
        head_ = static_cast<std::size_t>(0U);
        size_ = static_cast<std::size_t>(0U);
    }

private:
    std::vector<T> data_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
