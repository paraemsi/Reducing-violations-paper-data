#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

using Matrix = std::vector<std::vector<std::uint32_t>>;

/**
 * @brief Generate a clockwise spiral matrix of the specified size.
 *
 * The matrix is filled with natural numbers starting at 1 in the
 * top-left corner and progressing inward in a clockwise spiral.
 *
 * @param size Length of one side of the square matrix.
 * @return Matrix containing the spiral ordering. Returns an empty
 *         matrix when size is 0.
 */
auto spiral_matrix(std::uint32_t size) -> Matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
