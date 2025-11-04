#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : buf_(capacity), cap_(capacity) {}

    T read() {
        if (size_ == 0) {
            throw std::domain_error("Cannot read from an empty buffer");
        }
        T value = std::move(buf_[head_]);
        head_ = (head_ + 1) % cap_;
        --size_;
        return value;
    }

    void write(T value) {
        if (size_ == cap_) {
            throw std::domain_error("Cannot write to a full buffer");
        }
        buf_[tail_index()] = std::move(value);
        ++size_;
    }

    void overwrite(T value) {
        if (cap_ == 0) {
            return; // No capacity; ignore overwrite.
        }
        if (size_ == cap_) {
            // Overwrite the oldest and advance head.
            buf_[head_] = std::move(value);
            head_ = (head_ + 1) % cap_;
        } else {
            buf_[tail_index()] = std::move(value);
            ++size_;
        }
    }

    void clear() {
        head_ = 0;
        size_ = 0;
    }

private:
    std::size_t tail_index() const {
        // Only valid when cap_ > 0 and size_ < cap_.
        return (head_ + size_) % cap_;
    }

    std::vector<T> buf_;
    std::size_t cap_{0};
    std::size_t head_{0}; // Index of the oldest element.
    std::size_t size_{0}; // Number of stored elements.
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
