#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity), head_(0), tail_(0), size_(0) {}

    void write(const T& value) {
        if (full()) {
            throw std::runtime_error("Buffer is full");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % (buffer_.empty() ? 1 : buffer_.size());
        ++size_;
    }

    void overwrite(const T& value) {
        if (full()) {
            buffer_[tail_] = value;
            tail_ = (tail_ + 1) % (buffer_.empty() ? 1 : buffer_.size());
            head_ = (head_ + 1) % (buffer_.empty() ? 1 : buffer_.size());
        } else {
            write(value);
        }
    }

    T read() {
        if (empty()) {
            throw std::runtime_error("Buffer is empty");
        }
        T value = buffer_[head_];
        head_ = (head_ + 1) % (buffer_.empty() ? 1 : buffer_.size());
        --size_;
        return value;
    }

    void clear() {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == buffer_.size();
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return buffer_.size();
    }

private:
    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
