#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

using index_t = std::size_t;

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(index_t capacity);
    void write(const T& item);
    void overwrite(const T& item);
    T read();
    void clear();
    bool is_empty() const;
    bool is_full() const;
    index_t size() const;
    index_t capacity() const;

private:
    std::vector<T> buffer_;
    index_t capacity_;
    index_t head_;
    index_t tail_;
    index_t count_;
};

// Implementation

template <typename T>
circular_buffer<T>::circular_buffer(index_t capacity)
    : buffer_(capacity), capacity_(capacity), head_(0U), tail_(0U), count_(0U)
{
    // No further initialization required
}

template <typename T>
void circular_buffer<T>::write(const T& item)
{
    if (is_full()) {
        throw std::domain_error("Buffer is full");
    }
    buffer_[tail_] = item;
    tail_ = (tail_ + 1U) % capacity_;
    count_ = count_ + 1U;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& item)
{
    if (is_full()) {
        buffer_[tail_] = item;
        tail_ = (tail_ + 1U) % capacity_;
        head_ = (head_ + 1U) % capacity_;
        // count_ remains unchanged (buffer stays full)
    } else {
        write(item);
    }
}

template <typename T>
T circular_buffer<T>::read()
{
    if (is_empty()) {
        throw std::domain_error("Buffer is empty");
    }
    T value = buffer_[head_];
    head_ = (head_ + 1U) % capacity_;
    count_ = count_ - 1U;
    return value;
}

template <typename T>
void circular_buffer<T>::clear()
{
    head_ = 0U;
    tail_ = 0U;
    count_ = 0U;
}

template <typename T>
bool circular_buffer<T>::is_empty() const
{
    return (count_ == 0U);
}

template <typename T>
bool circular_buffer<T>::is_full() const
{
    return (count_ == capacity_);
}

template <typename T>
index_t circular_buffer<T>::size() const
{
    return count_;
}

template <typename T>
index_t circular_buffer<T>::capacity() const
{
    return capacity_;
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
