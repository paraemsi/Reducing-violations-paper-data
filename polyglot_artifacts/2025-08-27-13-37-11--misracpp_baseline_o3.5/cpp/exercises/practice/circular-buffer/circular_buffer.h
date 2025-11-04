#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

class buffer_empty_exception : public std::runtime_error {
 public:
  buffer_empty_exception() : std::runtime_error("empty buffer") {}
};

class buffer_full_exception : public std::runtime_error {
 public:
  buffer_full_exception() : std::runtime_error("full buffer") {}
};

template <typename T>
class circular_buffer {
 public:
  explicit circular_buffer(std::size_t capacity)
      : buffer_(capacity),
        capacity_(capacity),
        head_(0),
        tail_(0),
        full_(false) {}

  void clear() {
    head_ = tail_;
    full_ = false;
  }

  T read() {
    if (is_empty()) {
      throw buffer_empty_exception();
    }
    T value = buffer_[tail_];
    tail_ = (tail_ + 1) % capacity_;
    full_ = false;
    return value;
  }

  void write(const T& value) {
    if (full_) {
      throw buffer_full_exception();
    }
    buffer_[head_] = value;
    advance_head();
  }

  void overwrite(const T& value) {
    if (full_) {
      buffer_[head_] = value;
      advance_head();
      tail_ = head_;
    } else {
      write(value);
    }
  }

 private:
  bool is_empty() const { return !full_ && (head_ == tail_); }

  void advance_head() {
    head_ = (head_ + 1) % capacity_;
    if (head_ == tail_) {
      full_ = true;
    }
  }

  std::vector<T> buffer_;
  std::size_t capacity_;
  std::size_t head_;
  std::size_t tail_;
  bool full_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
