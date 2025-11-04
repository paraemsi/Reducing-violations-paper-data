#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

using matrix_t = std::vector<std::vector<std::uint32_t>>;

/*
 * Return a square matrix of the given size filled with
 * increasing natural numbers in a clockwise spiral order.
 */
auto spiral_matrix(std::uint32_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
