#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

/* Build a size x size matrix filled with natural numbers starting at 1,
 * arranged in a clockwise spiral order.
 */
using matrix = std::vector<std::vector<std::uint32_t>>;
auto spiral_matrix(std::size_t size) noexcept -> matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
