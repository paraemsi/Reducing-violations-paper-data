#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

struct buffer_empty {};
struct buffer_full {};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_{capacity}, buffer_(capacity), head_{0}, size_{0} {}

    T read() {
        if (size_ == 0) {
            throw std::domain_error("empty buffer");
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (capacity_ == 0 || size_ == capacity_) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_index()] = value;
        ++size_;
    }

    void write(T&& value) {
        if (capacity_ == 0 || size_ == capacity_) {
            throw std::domain_error("full buffer");
        }
        buffer_[tail_index()] = std::move(value);
        ++size_;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return;
        }
        if (size_ == capacity_) {
            buffer_[head_] = value;
            head_ = (head_ + 1) % capacity_;
        } else {
            buffer_[tail_index()] = value;
            ++size_;
        }
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) {
            return;
        }
        if (size_ == capacity_) {
            buffer_[head_] = std::move(value);
            head_ = (head_ + 1) % capacity_;
        } else {
            buffer_[tail_index()] = std::move(value);
            ++size_;
        }
    }

    void clear() noexcept {
        head_ = 0;
        size_ = 0;
    }

private:
    std::size_t capacity_;
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t size_;

    std::size_t tail_index() const {
        return (head_ + size_) % capacity_;
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
