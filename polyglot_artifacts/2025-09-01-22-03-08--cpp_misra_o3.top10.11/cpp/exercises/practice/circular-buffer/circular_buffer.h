#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/* Exception raised when attempting to write to a full buffer */
class buffer_full_error final : public std::runtime_error {
public:
    buffer_full_error() : std::runtime_error("circular buffer is full") {}
};

/* Exception raised when attempting to read from an empty buffer */
class buffer_empty_error final : public std::runtime_error {
public:
    buffer_empty_error() : std::runtime_error("circular buffer is empty") {}
};

/*
 * Fixed-size circular (ring) buffer for integral data.
 * The implementation is single-producer / single-consumer and not thread-safe.
 */
template <typename T>
class circular_buffer final {
public:
    using value_type = T;

    explicit circular_buffer(std::size_t capacity);

    void write(value_type value);      /* write or throw buffer_full_error      */
    void overwrite(value_type value);  /* write, overwriting oldest if full     */
    value_type read();                 /* read or throw buffer_empty_error      */
    void clear();                      /* remove all elements                   */

    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] bool full()  const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;

private:
    std::vector<value_type> data_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};

/* ======= Template implementation ================================================= */
template <typename T>
inline circular_buffer<T>::circular_buffer(std::size_t capacity)
    : data_(capacity),
      head_(0U),
      tail_(0U),
      count_(0U) {
    /* capacity must be non-zero */
    if (capacity == static_cast<std::size_t>(0)) {
        throw std::invalid_argument("capacity must be greater than zero");
    }
}

template <typename T>
inline bool circular_buffer<T>::empty() const noexcept {
    return (count_ == 0U);
}

template <typename T>
inline bool circular_buffer<T>::full() const noexcept {
    return (count_ == data_.size());
}

template <typename T>
inline std::size_t circular_buffer<T>::size() const noexcept {
    return count_;
}

template <typename T>
inline std::size_t circular_buffer<T>::capacity() const noexcept {
    return data_.size();
}

template <typename T>
inline void circular_buffer<T>::write(typename circular_buffer<T>::value_type value) {
    if (full()) {
        throw buffer_full_error();
    }
    data_[tail_] = value;
    tail_ = (tail_ + static_cast<std::size_t>(1)) % data_.size();
    ++count_;
}

template <typename T>
inline void circular_buffer<T>::overwrite(typename circular_buffer<T>::value_type value) {
    const bool was_full { full() };

    data_[tail_] = value;

    if (was_full) {
        head_ = (head_ + static_cast<std::size_t>(1)) % data_.size();  /* discard oldest */
    } else {
        ++count_;
    }

    tail_ = (tail_ + static_cast<std::size_t>(1)) % data_.size();
}

template <typename T>
inline typename circular_buffer<T>::value_type circular_buffer<T>::read() {
    if (empty()) {
        throw buffer_empty_error();
    }

    const value_type result { data_[head_] };
    head_ = (head_ + static_cast<std::size_t>(1)) % data_.size();
    --count_;
    return result;
}

template <typename T>
inline void circular_buffer<T>::clear() {
    head_  = 0U;
    tail_  = 0U;
    count_ = 0U;
}
/* ================================================================================ */

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
