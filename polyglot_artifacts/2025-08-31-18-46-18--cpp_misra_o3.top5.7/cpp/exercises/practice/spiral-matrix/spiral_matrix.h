#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

using matrix_type = std::vector<std::vector<std::uint32_t>>;

/*  Generate a square matrix of the requested size filled in clockwise
 *  spiral order starting with 1 in the top-left corner.
 *
 *  Example (size == 3):
 *  1 2 3
 *  8 9 4
 *  7 6 5
 */
auto spiral_matrix(std::uint32_t size) -> matrix_type;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
