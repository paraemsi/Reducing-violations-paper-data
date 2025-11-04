#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>

namespace circular_buffer {

template <typename T>
class circular_buffer {
public:
    explicit circular_buffer(std::uint32_t capacity)
        : buffer(nullptr),
          capacity_(capacity), 
          read_pos_(0U), 
          write_pos_(0U), 
          count_(0U) {
        if (capacity_ == 0U) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
        buffer = new T[capacity_];
    }
    
    ~circular_buffer() {
        delete[] buffer;
    }
    
    void write(const T& data) {
        if (count_ == capacity_) {
            throw std::domain_error("Buffer is full");
        }
        buffer[write_pos_] = data;
        write_pos_ = ((write_pos_ + 1U) % capacity_);
        count_ = (count_ + 1U);
    }
    
    void overwrite(const T& data) {
        if (count_ < capacity_) {
            write(data);
        } else {
            buffer[write_pos_] = data;
            write_pos_ = ((write_pos_ + 1U) % capacity_);
            read_pos_ = ((read_pos_ + 1U) % capacity_);
        }
    }
    
    T read() {
        if (count_ == 0U) {
            throw std::domain_error("Buffer is empty");
        }
        T data = buffer[read_pos_];
        read_pos_ = ((read_pos_ + 1U) % capacity_);
        count_ = (count_ - 1U);
        return data;
    }
    
    void clear() {
        read_pos_ = 0U;
        write_pos_ = 0U;
        count_ = 0U;
    }
    
    // Delete copy constructor and assignment operator
    circular_buffer(const circular_buffer&) = delete;
    circular_buffer& operator=(const circular_buffer&) = delete;
    
private:
    T* buffer;
    std::uint32_t capacity_;
    std::uint32_t read_pos_;
    std::uint32_t write_pos_;
    std::uint32_t count_;
};

}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H
