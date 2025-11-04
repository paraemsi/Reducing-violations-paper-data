#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

using value_type = int;
using matrix = std::vector<std::vector<value_type>>;

// Generate a square matrix of the given size filled in a clockwise spiral with values starting at 1.
auto spiral_matrix(std::size_t size) -> matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
