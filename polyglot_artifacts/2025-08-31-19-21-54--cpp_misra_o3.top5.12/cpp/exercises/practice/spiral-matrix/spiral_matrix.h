#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

using matrix_t = std::vector<std::vector<std::uint32_t>>;

/*
 * Generate a size x size spiral matrix containing natural numbers
 * starting at 1 and increasing clockwise toward the centre.
 *
 * \param size  The width and height of the required square matrix.
 * \return      matrix_t containing the generated spiral.
 */
auto spiral_matrix(std::size_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
