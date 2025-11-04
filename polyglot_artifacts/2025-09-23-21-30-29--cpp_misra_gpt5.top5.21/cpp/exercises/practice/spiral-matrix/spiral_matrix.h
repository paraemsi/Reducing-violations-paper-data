#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

/* Generate a square matrix of the given size filled in a clockwise spiral order.
   Returns an empty matrix when size is 0. */
using value_type = std::int32_t;
std::vector<std::vector<value_type>> spiral_matrix(std::uint32_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
