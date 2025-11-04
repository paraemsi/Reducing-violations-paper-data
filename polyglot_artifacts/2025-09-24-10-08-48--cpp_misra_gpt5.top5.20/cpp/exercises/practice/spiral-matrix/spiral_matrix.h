#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

using value_t = std::uint32_t;
using matrix_t = std::vector<std::vector<value_t>>;

auto spiral_matrix(value_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
