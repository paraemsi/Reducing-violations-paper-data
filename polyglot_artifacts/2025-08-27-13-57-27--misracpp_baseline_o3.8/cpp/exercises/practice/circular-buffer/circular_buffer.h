#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>

namespace circular_buffer {

// Exceptions the client code can catch
class buffer_full  : public std::domain_error {
public:
    buffer_full() : std::domain_error("full buffer") {}
};

class buffer_empty : public std::domain_error {
public:
    buffer_empty() : std::domain_error("empty buffer") {}
};

/*
 * Generic fixed-capacity circular (ring) buffer.
 *
 * All member functions are O(1).
 *
 * When the buffer is full:
 *   - write() throws buffer_full
 *   - overwrite() replaces the oldest element
 *
 * read() removes and returns the oldest element or throws buffer_empty
 * clear() removes all elements.
 */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : data_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          size_(0) {}

    // Add element, throw if buffer already full
    void write(T value) {
        if (size_ == capacity_) {
            throw std::domain_error("full buffer");
        }
        data_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    // Add element, overwriting the oldest if buffer is full
    void overwrite(T value) {
        if (capacity_ == 0) {
            return;               // nothing to store into
        }

        if (size_ == capacity_) { // full – replace oldest
            data_[head_] = value;
            head_ = (head_ + 1) % capacity_;
            tail_ = head_;
        } else {
            write(value);         // space available
        }
    }

    // Remove and return oldest element
    T read() {
        if (size_ == 0) {
            throw std::domain_error("empty buffer");
        }
        T value = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    // Empty the buffer
    void clear() {
        head_ = tail_ = size_ = 0;
    }

private:
    std::vector<T> data_;
    std::size_t    capacity_;
    std::size_t    head_;   // index of next element to read
    std::size_t    tail_;   // index of next position to write
    std::size_t    size_;   // current number of stored elements
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
