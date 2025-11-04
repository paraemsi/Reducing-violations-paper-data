#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

// Alias for the matrix type – a square matrix of unsigned 32-bit integers.
using matrix = std::vector<std::vector<std::uint32_t>>;

/*
 * Generate a size×size spiral matrix filled with consecutive natural
 * numbers starting from 1 in clockwise order.
 *
 * \param size The width and height of the required square matrix.
 * \return     A clockwise-filled spiral matrix; empty when size == 0.
 */
auto generate(std::uint32_t size) -> matrix;
auto spiral_matrix(std::uint32_t size) -> matrix;   // compatibility wrapper

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
