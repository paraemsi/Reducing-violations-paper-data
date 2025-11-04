#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

using matrix_t = std::vector<std::vector<std::uint32_t>>;

matrix_t spiral(std::size_t size);
matrix_t spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
