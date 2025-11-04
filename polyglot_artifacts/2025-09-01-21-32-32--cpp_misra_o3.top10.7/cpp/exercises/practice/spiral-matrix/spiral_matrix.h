#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

using Element = std::int32_t;
using Matrix  = std::vector<std::vector<Element>>;

/**
 * \brief Generate a square matrix filled with a clockwise spiral of
 *        natural numbers, starting with 1 in the top-left corner.
 *
 * \param size Dimension of the required square matrix.
 * \return     A \ref Matrix containing the spiral; empty if \p size is 0.
 */
auto spiral_matrix(std::uint32_t size) -> Matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
