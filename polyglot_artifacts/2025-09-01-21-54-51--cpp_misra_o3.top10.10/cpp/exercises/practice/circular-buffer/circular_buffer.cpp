#include "circular_buffer.h"

namespace circular_buffer {

buffer_empty_exception::buffer_empty_exception()
    : std::domain_error("Circular buffer is empty") {
    /* no further action required */
}

buffer_full_exception::buffer_full_exception()
    : std::domain_error("Circular buffer is full") {
    /* no further action required */
}

}  // namespace circular_buffer
