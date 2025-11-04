#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H
#include <cstdint>
#include <vector>

namespace spiral_matrix {

using Matrix = std::vector<std::vector<std::uint32_t>>;

/**
 * @brief Generate a square matrix filled in a clockwise spiral pattern.
 *
 * @param size The dimension of the square matrix.
 * @return Matrix A two-dimensional vector containing the spiral.
 */
auto spiral_matrix(std::uint32_t size) -> Matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
