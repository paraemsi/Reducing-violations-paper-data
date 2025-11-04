#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace circular_buffer {
template <typename T>
class circular_buffer {
   public:
    explicit circular_buffer(size_t capacity)
        : capacity_(capacity), buffer_(capacity) {}

    T read() {
        if (count_ == 0) {
            throw std::domain_error("Buffer is empty");
        }
        T value = std::move(buffer_[head_].value());
        buffer_[head_].reset();
        head_ = (head_ + 1) % capacity_;
        count_--;
        return value;
    }

    void write(const T& value) {
        if (count_ == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_].emplace(value);
        tail_ = (tail_ + 1) % capacity_;
        count_++;
    }

    void write(T&& value) {
        if (count_ == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[tail_].emplace(std::move(value));
        tail_ = (tail_ + 1) % capacity_;
        count_++;
    }

    void overwrite(const T& value) {
        if (capacity_ == 0) {
            return;
        }

        buffer_[tail_].emplace(value);

        if (count_ < capacity_) {
            count_++;
        } else {
            head_ = (head_ + 1) % capacity_;
        }
        tail_ = (tail_ + 1) % capacity_;
    }

    void overwrite(T&& value) {
        if (capacity_ == 0) {
            return;
        }

        buffer_[tail_].emplace(std::move(value));

        if (count_ < capacity_) {
            count_++;
        } else {
            head_ = (head_ + 1) % capacity_;
        }
        tail_ = (tail_ + 1) % capacity_;
    }

    void clear() {
        for (auto& item : buffer_) {
            item.reset();
        }
        head_ = 0;
        tail_ = 0;
        count_ = 0;
    }

   private:
    size_t capacity_;
    std::vector<std::optional<T>> buffer_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t count_ = 0;
};
}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
