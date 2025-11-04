#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>
#include <cstddef>

namespace spiral_matrix {

using value_type = int;
using matrix = std::vector<std::vector<value_type>>;

auto spiral_matrix(std::size_t size) -> matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
