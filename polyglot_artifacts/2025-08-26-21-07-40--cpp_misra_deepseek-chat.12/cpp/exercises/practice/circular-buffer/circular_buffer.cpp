#include "circular_buffer.h"

namespace circular_buffer {

// Explicit instantiations for common types
template class circular_buffer<int>;
template class circular_buffer<char>;
template class circular_buffer<double>;

}  // namespace circular_buffer
