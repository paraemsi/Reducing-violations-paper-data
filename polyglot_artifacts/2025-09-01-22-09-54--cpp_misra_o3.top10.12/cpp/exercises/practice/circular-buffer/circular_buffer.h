#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/*!
 * \brief A fixed-capacity ring buffer that supports write, overwrite and read
 *        operations.  When full, write() throws while overwrite() replaces the
 *        oldest element.
 *
 * \tparam T Stored element type – must be default-constructible and assignable.
 */
template<typename T>
class circular_buffer
{
public:
    explicit CircularBuffer(std::size_t max_capacity);

    void write(const T& item);
    void overwrite(const T& item);
    T read();

    void clear() noexcept;

    [[nodiscard]] bool is_empty() const noexcept;
    [[nodiscard]] bool is_full() const noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;

private:
    std::vector<T> buffer_;   // underlying storage
    std::size_t     head_{0U};     // index of the oldest element
    std::size_t     size_{0U};     // current number of stored elements
    std::size_t     capacity_{0U}; // maximum number of elements

    [[nodiscard]] std::size_t next_index(std::size_t index) const noexcept;
};

/* Provide a PascalCase alias for backward compatibility with other codebases */
template<typename T>
using CircularBuffer = circular_buffer<T>;
 
/* ========  template implementations  ======== */

template<typename T>
circular_buffer<T>::circular_buffer(std::size_t max_capacity) :
    buffer_(max_capacity),
    head_(0U),
    size_(0U),
    capacity_(max_capacity)
{
    if (max_capacity == 0U) {
        throw std::invalid_argument("CircularBuffer capacity must be greater than zero");
    }
}

template<typename T>
void circular_buffer<T>::write(const T& item)
{
    if (is_full()) {
        throw std::domain_error("CircularBuffer is full");
    }

    const std::size_t write_pos = (head_ + size_) % capacity_;
    buffer_[write_pos] = item;
    size_ += 1U;
}

template<typename T>
void circular_buffer<T>::overwrite(const T& item)
{
    if (is_full()) {
        buffer_[head_] = item;
        head_ = next_index(head_);
    } else {
        write(item);
    }
}

template<typename T>
T circular_buffer<T>::read()
{
    if (is_empty()) {
        throw std::domain_error("CircularBuffer is empty");
    }

    T value = buffer_[head_];
    head_ = next_index(head_);
    size_ -= 1U;
    return value;
}

template<typename T>
void circular_buffer<T>::clear() noexcept
{
    head_ = 0U;
    size_ = 0U;
}

template<typename T>
bool circular_buffer<T>::is_empty() const noexcept
{
    return size_ == 0U;
}

template<typename T>
bool circular_buffer<T>::is_full() const noexcept
{
    return size_ == capacity_;
}

template<typename T>
std::size_t circular_buffer<T>::capacity() const noexcept
{
    return capacity_;
}

template<typename T>
std::size_t circular_buffer<T>::size() const noexcept
{
    return size_;
}

template<typename T>
std::size_t circular_buffer<T>::next_index(std::size_t index) const noexcept
{
    return (index + 1U) % capacity_;
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
