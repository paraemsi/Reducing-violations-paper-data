#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

using value_type = std::uint32_t;
using matrix_t = std::vector<std::vector<value_type>>;

matrix_t spiral_matrix(std::size_t size);
matrix_t generate(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
