#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

using value_type = int;
using matrix = std::vector<std::vector<value_type>>;

// Return a size x size matrix filled in a clockwise spiral starting at 1 in the top-left.
[[nodiscard]] auto spiral_matrix(std::size_t size) -> matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
