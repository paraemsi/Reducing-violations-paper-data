#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

using matrix = std::vector<std::vector<int>>;

auto spiral_matrix(std::size_t size) -> matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
