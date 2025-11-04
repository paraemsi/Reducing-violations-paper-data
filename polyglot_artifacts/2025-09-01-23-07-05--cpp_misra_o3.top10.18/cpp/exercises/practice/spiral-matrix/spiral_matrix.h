#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

/**
 * @brief Generate a square spiral matrix of the specified size.
 *
 * @param size The length of each side of the square matrix.
 * @return A two-dimensional vector containing the spiral-ordered numbers.
 */
auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
