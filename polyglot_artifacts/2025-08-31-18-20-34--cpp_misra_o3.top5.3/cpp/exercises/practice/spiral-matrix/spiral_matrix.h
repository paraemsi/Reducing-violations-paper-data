#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

/**
 * @brief Build a clockwise spiral matrix.
 *
 * @param dimension Length of one edge of the square matrix
 * @return std::vector<std::vector<std::uint32_t>> Two-dimensional matrix filled
 *         with the numbers 1 … (dimension * dimension) in spiral order.
 */
auto spiral_matrix(std::size_t dimension) -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
