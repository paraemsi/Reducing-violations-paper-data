#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <utility>

namespace circular_buffer {

/* We rely directly on std::domain_error for signalling buffer
   under-flow and over-flow, so no custom exception types are needed. */

/* Fixed-size circular buffer holding generic values */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : data_(capacity), capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("capacity must be greater than zero");
        }
    }

    T read() {
        if (empty()) {
            throw std::domain_error("empty buffer");
        }
        T value = std::move(data_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    void write(const T& value) {
        if (full()) {
            throw std::domain_error("full buffer");
        }
        data_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void overwrite(const T& value) {
        if (full()) {
            data_[tail_] = value;            // overwrite the oldest (at current tail)
            head_ = (head_ + 1) % capacity_; // move head forward – new oldest element
            tail_ = (tail_ + 1) % capacity_; // move tail forward – next write location
            /* size_ stays the same (buffer remains full) */
        } else {
            write(value);
        }
    }

    void clear() noexcept {
        head_ = tail_ = size_ = 0;
    }

    bool empty() const noexcept { return size_ == 0; }
    bool full()  const noexcept { return size_ == capacity_; }

private:
    std::vector<T> data_;
    std::size_t head_{0};   // next position to read
    std::size_t tail_{0};   // next position to write
    std::size_t size_{0};   // current number of stored elements
    std::size_t capacity_;  // maximum size of buffer
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
