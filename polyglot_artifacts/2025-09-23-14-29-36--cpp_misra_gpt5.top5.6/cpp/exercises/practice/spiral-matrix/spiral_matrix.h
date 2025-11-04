#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>
#include <cstddef>

namespace spiral_matrix {

using value_type = std::int32_t;
using matrix_type = std::vector<std::vector<value_type>>;

auto spiral_matrix(std::size_t size) -> matrix_type;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
