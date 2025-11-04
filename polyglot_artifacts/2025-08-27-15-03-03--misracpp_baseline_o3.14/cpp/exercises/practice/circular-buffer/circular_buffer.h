#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    struct buffer_empty_exception : std::domain_error {
        buffer_empty_exception() : std::domain_error("circular_buffer empty") {}
    };
    struct buffer_full_exception  : std::domain_error {
        buffer_full_exception() : std::domain_error("circular_buffer full") {}
    };
    explicit circular_buffer(std::size_t capacity)
        : buffer_(capacity),
          capacity_(capacity),
          head_(0),
          tail_(0),
          size_(0) {}

    // Write a value to the buffer. Throws if the buffer is full.
    void write(const T& value)
    {
        if (is_full()) {
            throw buffer_full_exception();
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

        // Rvalue overload – enables move-only types and avoids copies.
        void write(T&& value)
        {
            if (is_full()) {
                throw buffer_full_exception{};
            }
            buffer_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % capacity_;
            ++size_;
        }

    // Read and remove the oldest value from the buffer.
    T read()
    {
        if (is_empty()) {
            throw buffer_empty_exception();
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;
        return value;
    }

    // Write a value, overwriting the oldest element if the buffer is full.
    void overwrite(const T& value)
    {
        if (is_full()) {
            // Write at the current tail position (equal to head_ when full),
            // then advance both pointers to keep the buffer in a consistent
            // "full" state where tail_ == head_.
            buffer_[tail_] = value;
            tail_ = (tail_ + 1) % capacity_;
            head_ = tail_;
        } else {
            write(value);
        }
    }

    // Overwrite using an rvalue – moves when possible.
    void overwrite(T&& value)
    {
        if (is_full()) {
            buffer_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % capacity_;
            head_ = tail_;
        } else {
            write(std::move(value));
        }
    }

    // Clear all elements from the buffer.
    void clear() noexcept
    {
        head_ = tail_ = size_ = 0;
    }

    bool is_empty() const noexcept { return size_ == 0; }
    bool is_full()  const noexcept { return size_ == capacity_; }

private:
    // internal data ----------------------------------------------------------------
    std::vector<T> buffer_;
    std::size_t    capacity_;
    std::size_t    head_;
    std::size_t    tail_;
    std::size_t    size_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
