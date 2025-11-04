#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

/* Generate a square matrix of size `size` filled in a clockwise spiral.
 * The result is a Matrix where Matrix is an alias for a two-dimensional
 * vector of std::uint32_t.
 */
using Matrix = std::vector<std::vector<std::uint32_t>>;

/*  Generate a clockwise-spiral matrix.
 *  The return value must be used – mark it [[nodiscard]].
 */
[[nodiscard]] auto spiral(std::uint32_t size) -> Matrix;

/* Wrapper required by the test-suite: same functionality as `spiral`. */
[[nodiscard]] auto spiral_matrix(std::uint32_t size) -> Matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
