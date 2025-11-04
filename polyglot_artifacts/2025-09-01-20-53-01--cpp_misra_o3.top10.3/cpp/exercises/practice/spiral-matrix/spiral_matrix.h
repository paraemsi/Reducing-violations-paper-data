#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

using matrix_t = std::vector<std::vector<std::uint32_t>>;

/* Return a size×size matrix filled 1 … size² in clockwise-spiral order */
auto spiral_matrix(std::uint32_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
