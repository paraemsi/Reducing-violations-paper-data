#include "circular_buffer.h"

namespace circular_buffer {

// Explicitly instantiate templates for common types
template class circular_buffer<int>;
template class circular_buffer<char>;
template class circular_buffer<double>;
template class circular_buffer<float>;
template class circular_buffer<long>;
template class circular_buffer<long long>;
template class circular_buffer<unsigned>;
template class circular_buffer<unsigned long>;
template class circular_buffer<unsigned long long>;

}  // namespace circular_buffer
