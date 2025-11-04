#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

/*
 * Generate a square matrix whose elements form a clockwise
 * spiral starting with 1 in the top-left corner.
 *
 * MISRA-C++ compliance:
 *  - Uses fixed-width unsigned integers (std::uint32_t).
 *  - No implicit integral conversions.
 */
[[nodiscard]] auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
