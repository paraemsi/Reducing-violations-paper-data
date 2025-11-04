#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

using matrix = std::vector<std::vector<std::uint32_t>>;

/*
 * Return a square matrix of the requested size filled in a clockwise
 * spiral starting with 1 in the top-left corner.
 *
 * size == 0 → returns an empty matrix.
 */
auto spiral_matrix(std::uint32_t size) -> matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
