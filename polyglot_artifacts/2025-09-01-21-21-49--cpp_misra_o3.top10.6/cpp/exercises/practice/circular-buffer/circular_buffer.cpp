#include "circular_buffer.h"

#include <cstdint>

namespace circular_buffer
{
// Explicit instantiation for a common type; users may instantiate others.
template class circular_buffer<std::int32_t>;
}  // namespace circular_buffer
