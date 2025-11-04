#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H
#include <vector>
#include <optional>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <algorithm>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity);

    void write(const T& item);       // add a value, throw if buffer full
    void overwrite(const T& item);   // add a value, overwrite oldest if full
    T read();                        // remove and return oldest value, throw if empty
    void clear();                    // remove all elements

private:
    bool empty() const;
    bool full() const;

    std::vector<std::optional<T>> buffer_;
    std::size_t head_{0};   // next write position
    std::size_t tail_{0};   // next read position
    bool full_{false};      // flag distinguishing full from empty when head_ == tail_
    std::size_t capacity_;
};

/* ---- implementation ---- */

template <typename T>
circular_buffer<T>::circular_buffer(std::size_t capacity)
    : buffer_(capacity), capacity_(capacity) {
    if (capacity == 0) {
        throw std::domain_error("capacity must be greater than 0");
    }
}

template <typename T>
bool circular_buffer<T>::empty() const {
    return !full_ && (head_ == tail_);
}

template <typename T>
bool circular_buffer<T>::full() const {
    return full_;
}

template <typename T>
void circular_buffer<T>::write(const T& item) {
    if (full()) {
        throw std::domain_error("buffer is full");
    }
    buffer_[head_] = item;
    head_ = (head_ + 1) % capacity_;
    if (head_ == tail_) {
        full_ = true;
    }
}

template <typename T>
void circular_buffer<T>::overwrite(const T& item) {
    if (full()) {
        buffer_[head_] = item;
        head_ = (head_ + 1) % capacity_;
        tail_ = head_;
    } else {
        write(item);
    }
}

template <typename T>
T circular_buffer<T>::read() {
    if (empty()) {
        throw std::domain_error("buffer is empty");
    }
    T value = std::move(*buffer_[tail_]);
    buffer_[tail_].reset();
    tail_ = (tail_ + 1) % capacity_;
    full_ = false;
    return value;
}

template <typename T>
void circular_buffer<T>::clear() {
    std::fill(buffer_.begin(), buffer_.end(), std::nullopt);
    head_ = 0;
    tail_ = 0;
    full_ = false;
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
