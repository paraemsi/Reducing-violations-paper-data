#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

using element_t = std::int32_t;
using matrix_t  = std::vector<std::vector<element_t>>;

/*
 * Generate a square matrix of the requested size and fill it
 * with consecutive natural numbers in a clockwise spiral order,
 * starting with 1 in the top-left corner.
 *
 * The function returns an empty matrix when size == 0.
 */
auto spiral_matrix(std::uint32_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
