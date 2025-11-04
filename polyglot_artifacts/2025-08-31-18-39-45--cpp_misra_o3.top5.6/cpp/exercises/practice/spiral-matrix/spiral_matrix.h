#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

/* Alias for the matrix type used by the exercise */
using matrix_t = std::vector<std::vector<std::uint32_t>>;

/* Return a square matrix whose elements form a clockwise spiral
 * starting with 1 in the upper-left corner.
 */
auto spiral_matrix(std::uint32_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
