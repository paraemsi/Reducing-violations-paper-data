#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

struct buffer_empty_exception : std::domain_error {
    buffer_empty_exception() : std::domain_error("circular buffer is empty") {}
};

struct buffer_full_exception : std::domain_error {
    buffer_full_exception() : std::domain_error("circular buffer is full") {}
};

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : data_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          size_(0) {}

    T read() {
        if (size_ == 0) {
            throw buffer_empty_exception();
        }
        T value = std::move(data_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(T value) {
        if (capacity_ == 0 || size_ == capacity_) {
            throw buffer_full_exception();
        }
        data_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void overwrite(T value) {
        if (capacity_ == 0) {
            return; // nothing to store
        }
        if (size_ == capacity_) {
            // buffer full: overwrite oldest element and advance both head and tail
            data_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % capacity_;
            head_ = (head_ + 1) % capacity_;
            // size_ remains at capacity_
        } else {
            data_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % capacity_;
            ++size_;
        }
    }

    void clear() {
        head_ = tail_ = 0;
        size_ = 0;
    }

private:
    std::vector<T> data_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
