#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>
#include <cstdint>

namespace spiral_matrix {

using matrix_t = std::vector<std::vector<std::int32_t>>;

matrix_t spiral(const std::size_t size);
matrix_t spiral_matrix(const std::size_t size);
matrix_t generate(const std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
