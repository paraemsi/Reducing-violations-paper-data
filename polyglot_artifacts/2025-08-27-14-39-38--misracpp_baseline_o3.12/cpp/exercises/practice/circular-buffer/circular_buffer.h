#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
 public:
  explicit circular_buffer(std::size_t capacity);

  // Add an element to the buffer if space is available.
  // Throws std::domain_error if the buffer is already full.
  void write(const T& value);

  // Remove and return the oldest element.
  // Throws std::domain_error if the buffer is empty.
  T read();

  // Add an element, overwriting the oldest when the buffer is full.
  void overwrite(const T& value);

  // Remove all elements.
  void clear();

  // Current number of stored elements.
  std::size_t size() const noexcept { return size_; }

  // Maximum capacity of the buffer.
  std::size_t capacity() const noexcept { return capacity_; }

 private:
  std::vector<std::optional<T>> buffer_;
  std::size_t capacity_;
  std::size_t head_;  // index of the next element to read
  std::size_t tail_;  // index of the next position to write
  std::size_t size_;
};

// ---- Template definitions ----
template <typename T>
circular_buffer<T>::circular_buffer(std::size_t capacity)
    : buffer_(capacity),
      capacity_(capacity),
      head_(0),
      tail_(0),
      size_(0) {
  if (capacity == 0) {
    throw std::domain_error("Circular buffer capacity must be > 0");
  }
}

template <typename T>
void circular_buffer<T>::write(const T& value) {
  if (size_ == capacity_) {
    throw std::domain_error("Circular buffer is full");
  }

  buffer_[tail_] = value;
  tail_ = (tail_ + 1) % capacity_;
  ++size_;
}

template <typename T>
T circular_buffer<T>::read() {
  if (size_ == 0) {
    throw std::domain_error("Circular buffer is empty");
  }

  T value = std::move(*buffer_[head_]);
  buffer_[head_].reset();
  head_ = (head_ + 1) % capacity_;
  --size_;
  return value;
}

template <typename T>
void circular_buffer<T>::overwrite(const T& value) {
  if (size_ == capacity_) {
    // Drop oldest value (advance head).
    head_ = (head_ + 1) % capacity_;
  } else {
    ++size_;
  }

  buffer_[tail_] = value;
  tail_ = (tail_ + 1) % capacity_;
}

template <typename T>
void circular_buffer<T>::clear() {
  buffer_.assign(capacity_, std::nullopt);
  head_ = tail_ = size_ = 0;
}

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
