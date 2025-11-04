#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

class buffer_empty final : public std::domain_error {
public:
    buffer_empty() : std::domain_error("circular buffer empty") {}
};

class buffer_full final : public std::domain_error {
public:
    buffer_full() : std::domain_error("circular buffer full") {}
};

template <typename T>
class circular_buffer final {
public:
    explicit circular_buffer(std::size_t capacity)
        : capacity_(capacity),
          data_(capacity),
          head_(static_cast<std::size_t>(0U)),
          tail_(static_cast<std::size_t>(0U)),
          full_(false)
    {
        if(capacity == static_cast<std::size_t>(0U)) {
            throw std::invalid_argument("capacity must be > 0");
        }
    }

    T read()
    {
        if(is_empty()) {
            throw std::domain_error("circular buffer empty");
        }

        T value = data_[head_];
        advance_head();
        full_ = false;
        return value;
    }

    void write(const T& value)
    {
        if(full_) {
            throw std::domain_error("circular buffer full");
        }

        data_[tail_] = value;
        advance_tail();
    }

    void overwrite(const T& value)
    {
        if(full_) {
            data_[head_] = value;
            advance_head();
            /* maintain ‘full_’ invariant */ 
            advance_tail();
        } else {
            write(value);
        }
    }

    void clear() noexcept
    {
        head_ = static_cast<std::size_t>(0U);
        tail_ = static_cast<std::size_t>(0U);
        full_ = false;
    }

private:
    std::size_t capacity_;
    std::vector<T> data_;
    std::size_t head_;
    std::size_t tail_;
    bool full_;

    [[nodiscard]] bool is_empty() const noexcept
    {
        return ((!full_) && (head_ == tail_));
    }

    void advance_head() noexcept
    {
        head_ = ((head_ + static_cast<std::size_t>(1U)) % capacity_);
    }

    void advance_tail() noexcept
    {
        tail_ = ((tail_ + static_cast<std::size_t>(1U)) % capacity_);
        if(tail_ == head_) {
            full_ = true;
        }
    }
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
