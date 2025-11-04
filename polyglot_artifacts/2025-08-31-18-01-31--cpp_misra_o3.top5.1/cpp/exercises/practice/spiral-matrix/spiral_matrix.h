#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>
#include <cstdint>

namespace spiral_matrix {

using element_t = std::uint32_t;
using matrix_t  = std::vector<std::vector<element_t>>;

/**
 * @brief Generate a square spiral matrix of the specified size.
 *
 * The matrix is filled with consecutive natural numbers starting from 1 in
 * a clockwise spiral order.
 *
 * @param size  The width and height of the square matrix.
 * @return matrix_t The generated spiral matrix. If size is 0 an empty
 *                  matrix is returned.
 */
matrix_t spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
