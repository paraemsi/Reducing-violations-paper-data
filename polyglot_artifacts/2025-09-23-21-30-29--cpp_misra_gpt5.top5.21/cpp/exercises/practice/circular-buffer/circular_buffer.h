#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

struct buffer_empty final : public std::domain_error {
    buffer_empty() : std::domain_error("circular_buffer: buffer is empty") {}
};

struct buffer_full final : public std::domain_error {
    buffer_full() : std::domain_error("circular_buffer: buffer is full") {}
};

template <typename T>
class circular_buffer final {
public:
    explicit circular_buffer(std::size_t capacity)
        : storage_(capacity),
          head_(static_cast<std::size_t>(0)),
          tail_(static_cast<std::size_t>(0)),
          count_(static_cast<std::size_t>(0)),
          cap_(capacity) {
        if ((capacity) == (static_cast<std::size_t>(0))) {
            throw std::invalid_argument("circular_buffer: capacity must be > 0");
        }
    }

    void clear() noexcept {
        head_ = static_cast<std::size_t>(0);
        tail_ = static_cast<std::size_t>(0);
        count_ = static_cast<std::size_t>(0);
    }

    std::size_t capacity() const noexcept {
        return cap_;
    }

    std::size_t size() const noexcept {
        return count_;
    }

    bool empty() const noexcept {
        return (count_ == static_cast<std::size_t>(0));
    }

    bool full() const noexcept {
        return (count_ == cap_);
    }

    void write(const T& value) {
        if (full()) {
            throw buffer_full();
        } else {
            storage_[head_] = value;
            head_ = ((head_ + static_cast<std::size_t>(1)) % cap_);
            count_ = (count_ + static_cast<std::size_t>(1));
        }
    }

    void overwrite(const T& value) {
        storage_[head_] = value;
        head_ = ((head_ + static_cast<std::size_t>(1)) % cap_);
        if (full()) {
            tail_ = ((tail_ + static_cast<std::size_t>(1)) % cap_);
        } else {
            count_ = (count_ + static_cast<std::size_t>(1));
        }
    }

    T read() {
        if (empty()) {
            throw buffer_empty();
        } else {
            T value = std::move(storage_[tail_]);
            tail_ = ((tail_ + static_cast<std::size_t>(1)) % cap_);
            count_ = (count_ - static_cast<std::size_t>(1));
            return value;
        }
    }

private:
    std::vector<T> storage_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
    std::size_t cap_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
