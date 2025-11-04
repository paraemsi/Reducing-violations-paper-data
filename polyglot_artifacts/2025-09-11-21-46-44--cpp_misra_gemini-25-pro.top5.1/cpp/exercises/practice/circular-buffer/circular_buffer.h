#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_(capacity), buffer_(capacity) {
        if (capacity == std::size_t{0}) {
            throw std::invalid_argument("Capacity cannot be zero");
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("Buffer is empty");
        }

        T value = buffer_.at(head_);
        head_ = ((head_ + std::size_t{1}) % capacity_);
        size_--;
        return value;
    }

    void write(const T &item) {
        if (full()) {
            throw std::domain_error("Buffer is full");
        }

        buffer_.at(tail_) = item;
        tail_ = ((tail_ + std::size_t{1}) % capacity_);
        size_++;
    }

    void overwrite(const T &item) {
        buffer_.at(tail_) = item;
        if (!full()) {
            size_++;
        } else {
            head_ = ((head_ + std::size_t{1}) % capacity_);
        }
        tail_ = ((tail_ + std::size_t{1}) % capacity_);
    }

    void clear() {
        head_ = std::size_t{0};
        tail_ = std::size_t{0};
        size_ = std::size_t{0};
    }

private:
    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == capacity_;
    }

    std::size_t capacity_;
    std::vector<T> buffer_;
    std::size_t head_{std::size_t{0}};
    std::size_t tail_{std::size_t{0}};
    std::size_t size_{std::size_t{0}};
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
