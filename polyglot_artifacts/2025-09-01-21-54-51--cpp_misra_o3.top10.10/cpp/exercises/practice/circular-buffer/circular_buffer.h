#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/* Exception raised when attempting to read from an empty buffer */
class buffer_empty_exception : public std::domain_error {
public:
    buffer_empty_exception();
};

/* Exception raised when attempting to write to a full buffer */
class buffer_full_exception : public std::domain_error {
public:
    buffer_full_exception();
};

/*
 * A fixed-capacity circular (ring) buffer.
 * The buffer supports write, overwrite, read and clear operations.
 * When the buffer is full a normal write() will throw buffer_full_exception.
 * overwrite() always succeeds, replacing the oldest element when necessary.
 */
template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity);

    void write(const T& value);
    void overwrite(const T& value);
    T read();
    void clear();

private:
    std::vector<T> buffer_;
    std::size_t capacity_;
    std::size_t head_; /* next position to write */
    std::size_t tail_; /* next position to read  */
    bool full_;        /* true when buffer contains capacity_ elements */

    bool is_empty() const noexcept;
    bool is_full() const noexcept;
};

/* -----------------  template implementation ----------------- */

template <typename T>
circular_buffer<T>::circular_buffer(std::size_t capacity)
    : buffer_(capacity),
      capacity_(capacity),
      head_(static_cast<std::size_t>(0)),
      tail_(static_cast<std::size_t>(0)),
      full_(false) {
    /* no further action required */
}

template <typename T>
void circular_buffer<T>::write(const T& value) {
    if (is_full()) {
        throw buffer_full_exception();
    } else {
        buffer_[head_] = value;
        head_ = (head_ + static_cast<std::size_t>(1)) % capacity_;
        if (head_ == tail_) {
            full_ = true;
        }
    }
}

template <typename T>
void circular_buffer<T>::overwrite(const T& value) {
    /* When the buffer is full we must drop the oldest element (at tail_)
     * before writing the new one.  Advance tail_ first, then reuse the
     * ordinary write() path which will place the element at head_ and
     * restore the full_ flag when appropriate.
     */
    if (is_full()) {
        tail_ = (tail_ + static_cast<std::size_t>(1)) % capacity_;
        full_ = false; /* buffer now considered not full for the upcoming write */
    }
    write(value);
}

template <typename T>
T circular_buffer<T>::read() {
    if (is_empty()) {
        throw buffer_empty_exception();
    } else {
        T value{ buffer_[tail_] };
        full_ = false;
        tail_ = (tail_ + static_cast<std::size_t>(1)) % capacity_;
        return value;
    }
}

template <typename T>
void circular_buffer<T>::clear() {
    head_ = static_cast<std::size_t>(0);
    tail_ = static_cast<std::size_t>(0);
    full_ = false;
}

template <typename T>
bool circular_buffer<T>::is_empty() const noexcept {
    return ((head_ == tail_) && (!full_));
}

template <typename T>
bool circular_buffer<T>::is_full() const noexcept {
    return full_;
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
