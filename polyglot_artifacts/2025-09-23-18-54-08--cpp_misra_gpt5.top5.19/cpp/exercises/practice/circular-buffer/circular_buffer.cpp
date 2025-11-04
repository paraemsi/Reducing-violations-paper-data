#include "circular_buffer.h"

namespace circular_buffer {

buffer_empty::buffer_empty() : std::domain_error("circular buffer empty") {}

buffer_full::buffer_full() : std::domain_error("circular buffer full") {}

}  // namespace circular_buffer
