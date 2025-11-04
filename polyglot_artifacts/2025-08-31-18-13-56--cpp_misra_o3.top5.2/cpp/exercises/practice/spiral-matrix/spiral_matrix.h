#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

/**
 * @brief Generate a square spiral matrix of the requested size.
 *
 * The matrix is filled with incrementing natural numbers starting with 1 in the
 * top-left corner and proceeding clockwise toward the centre.
 *
 * @param size The dimension of the matrix (number of rows and columns).
 * @return A two-dimensional vector containing the spiral matrix.
 */
[[nodiscard]] auto spiral_matrix(std::uint32_t size)
    -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
