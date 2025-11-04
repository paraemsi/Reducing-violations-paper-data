#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

using value_t  = int;                             // alias – raw type allowed only here
using matrix_t = std::vector<std::vector<value_t>>;

/*
 * Construct a square matrix whose elements form a clockwise
 * spiral starting with 1 in the top-left corner.
 *
 * size == 0 → empty matrix.
 */
auto spiral_matrix(std::size_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
