#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <memory>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_(capacity),
          size_(0),
          read_index_(0),
          write_index_(0) {
        if (capacity == 0) {
            throw std::invalid_argument("Buffer capacity must be greater than 0");
        }
        buffer_ = std::make_unique<T[]>(capacity);
    }

    void write(const T& item) {
        if (is_full()) {
            throw std::domain_error("Buffer is full");
        }
        buffer_[write_index_] = item;
        write_index_ = ((write_index_ + 1) % capacity_);
        size_ = size_ + 1;
    }

    void overwrite(const T& item) {
        bool was_full = is_full();
        buffer_[write_index_] = item;
        write_index_ = ((write_index_ + 1) % capacity_);
        
        if (was_full) {
            read_index_ = ((read_index_ + 1) % capacity_);
        } else {
            size_ = size_ + 1;
        }
    }

    T read() {
        if (is_empty()) {
            throw std::domain_error("Buffer is empty");
        }
        T item = buffer_[read_index_];
        read_index_ = ((read_index_ + 1) % capacity_);
        size_ = size_ - 1;
        return item;
    }

    void clear() {
        size_ = 0;
        read_index_ = 0;
        write_index_ = 0;
    }

    bool is_empty() const {
        return size_ == 0;
    }

    bool is_full() const {
        return size_ == capacity_;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

private:
    std::size_t capacity_;
    std::size_t size_;
    std::size_t read_index_;
    std::size_t write_index_;
    std::unique_ptr<T[]> buffer_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
