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
        : data_(capacity),
          head_(0),
          tail_(0),
          full_(false) {
        if (capacity == 0) {
            throw std::invalid_argument{"Capacity must be > 0"};
        }
    }

    // Write a new value, throwing if the buffer is already full
    void write(const T& value) {
        if (full_) {
            throw std::domain_error{"Buffer is full"};
        }
        data_[head_] = value;
        advance_head();
    }

    // Overwrite oldest value when buffer is full, otherwise behaves like write
    void overwrite(const T& value) {
        if (full_) {
            advance_tail();          // discard oldest
            full_ = false;           // buffer is no longer full after freeing a slot
        }
        data_[head_] = value;
        advance_head();
    }

    // Read and remove the oldest value, throwing if the buffer is empty
    T read() {
        if (empty()) {
            throw std::domain_error{"Buffer is empty"};
        }
        T value = data_[tail_];
        advance_tail();
        full_ = false;
        return value;
    }

    // Remove all elements
    void clear() noexcept {
        head_ = tail_ = 0;
        full_ = false;
    }

    // Current element count
    std::size_t size() const noexcept {
        if (full_) {
            return data_.size();
        }
        if (head_ >= tail_) {
            return head_ - tail_;
        }
        return data_.size() - (tail_ - head_);
    }

    // Buffer capacity
    std::size_t capacity() const noexcept {
        return data_.size();
    }

private:
    bool empty() const noexcept {
        return !full_ && (head_ == tail_);
    }

    void advance_head() noexcept {
        head_ = (head_ + 1) % data_.size();
        if (head_ == tail_) {
            full_ = true;
        }
    }

    void advance_tail() noexcept {
        tail_ = (tail_ + 1) % data_.size();
    }

    std::vector<T> data_;
    std::size_t head_;
    std::size_t tail_;
    bool full_;
};


}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
