#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

using index_t = std::uint32_t;

/**
 * \brief Generate a square matrix filled in clockwise spiral order.
 *
 * \param dimension Number of rows and columns of the resulting matrix.
 * \return Two-dimensional vector containing the spiral matrix.
 */
auto spiral(index_t dimension) -> std::vector<std::vector<index_t>>;

/* Public API required by the test-suite:
 * spiral_matrix::spiral_matrix(int dimension)
 * Accepts the (signed) literal supplied by the tests, performs an
 * explicit checked conversion to the unsigned index_t type, then
 * delegates to spiral().
 *
 * Keeping only this overload avoids an ambiguity between int and
 * index_t that arises during overload resolution.
 *
 * MISRA deviation: an explicit static_cast is applied in the
 * implementation to convert from signed to unsigned after a
 * non-negative range check.
 */
auto spiral_matrix(int dimension) -> std::vector<std::vector<index_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
