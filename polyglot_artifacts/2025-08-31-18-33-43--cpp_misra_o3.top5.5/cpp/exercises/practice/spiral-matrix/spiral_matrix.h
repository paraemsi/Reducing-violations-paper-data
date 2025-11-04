#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

/**
 * \brief Generate a clockwise spiral matrix of the requested size.
 *
 * \param size  The width and height of the square matrix to produce.
 * \return      A two-dimensional vector containing the spiral filled with the
 *              natural numbers starting at 1.
 */
auto spiral_matrix(std::uint32_t size)
    -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
