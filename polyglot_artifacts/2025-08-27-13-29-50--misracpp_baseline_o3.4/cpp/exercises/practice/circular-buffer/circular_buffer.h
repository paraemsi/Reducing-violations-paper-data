#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>     // for std::move

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          head_(0),
          tail_(0),
          size_(0),
          capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be > 0");
        }
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("Full buffer");
        }
        buffer_[tail_] = value;
        advance_tail();
    }

    void write(T&& value) {
        if (full()) {
            throw std::domain_error("Full buffer");
        }
        buffer_[tail_] = std::move(value);
        advance_tail();
    }

    void overwrite(const T& value) {
        if (full()) {
            buffer_[tail_] = value;
            head_ = (head_ + 1) % capacity_;
            tail_ = (tail_ + 1) % capacity_;
            /* size_ remains unchanged */
        } else {
            write(value);
        }
    }

    void overwrite(T&& value) {
        if (full()) {
            buffer_[tail_] = std::move(value);
            head_ = (head_ + 1) % capacity_;
            tail_ = (tail_ + 1) % capacity_;
            /* size_ remains unchanged */
        } else {
            write(std::move(value));
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("Empty buffer");
        }
        T value = std::move(buffer_[head_]);
        advance_head();
        return value;
    }

    void clear() {
        head_ = tail_ = size_ = 0;
    }

private:
    bool full() const noexcept {
        return size_ == capacity_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    void advance_head() noexcept {
        head_ = (head_ + 1) % capacity_;
        --size_;
    }

    void advance_tail() noexcept {
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    std::vector<T> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;
    std::size_t capacity_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
