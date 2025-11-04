#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

/* Generate a square matrix of the given size, filled with
 * sequential natural numbers in an inward clockwise spiral.
 */
auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
