#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace circular_buffer {

/* Exception thrown when attempting to read from an empty buffer */
struct buffer_empty final : public std::domain_error {
    buffer_empty() : std::domain_error("Circular buffer is empty") {}
};

/* Exception thrown when attempting to write to a full buffer */
struct buffer_full final : public std::domain_error {
    buffer_full() : std::domain_error("Circular buffer is full") {}
};

/*
 * A run-time sized circular buffer.
 * The capacity is supplied at construction; template parameterisation
 * was avoided to keep usage identical to the original Exercism interface.
 */
template <typename T>
class circular_buffer final {
public:
    explicit circular_buffer(std::uint32_t capacity) :
        buffer_(static_cast<std::size_t>(capacity)),
        capacity_(capacity),
        head_(static_cast<std::uint32_t>(0U)),
        size_(static_cast<std::uint32_t>(0U))
    {
        /* capacity shall be greater than zero */
        if (capacity_ == static_cast<std::uint32_t>(0U)) {
            throw std::invalid_argument("Capacity shall be > 0");
        }
    }

    /* Remove every element without changing the capacity */
    void clear() noexcept
    {
        head_ = static_cast<std::uint32_t>(0U);
        size_ = static_cast<std::uint32_t>(0U);
    }

    /* Read and remove the oldest element */
    T read()
    {
        if (size_ == static_cast<std::uint32_t>(0U)) {
            throw buffer_empty{};
        }

        const std::uint32_t index { head_ };
        head_ = increment_index(head_);
        --size_;

        return buffer_[static_cast<std::size_t>(index)];
    }

    /* Append an element – throws if the buffer is full */
    void write(const T& item)
    {
        if (size_ == capacity_) {
            throw buffer_full{};
        }

        const std::uint32_t tail { tail_index() };
        buffer_[static_cast<std::size_t>(tail)] = item;
        ++size_;
    }

    /* Append an element, overwriting the oldest element if the buffer is full */
    void overwrite(const T& item)
    {
        if (size_ == capacity_) {
            buffer_[static_cast<std::size_t>(head_)] = item;
            head_ = increment_index(head_);
        } else {
            write(item);
        }
    }

private:
    /* Advance an index, wrapping at capacity */
    std::uint32_t increment_index(std::uint32_t index) const noexcept
    {
        return static_cast<std::uint32_t>(
            (index + static_cast<std::uint32_t>(1U)) % capacity_);
    }

    /* Compute the index one past the newest element */
    std::uint32_t tail_index() const noexcept
    {
        return static_cast<std::uint32_t>((head_ + size_) % capacity_);
    }

    std::vector<T>   buffer_;   /* underlying storage                        */
    std::uint32_t    capacity_; /* total number of elements the buffer holds */
    std::uint32_t    head_;     /* index of the oldest element               */
    std::uint32_t    size_;     /* current number of stored elements         */
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
