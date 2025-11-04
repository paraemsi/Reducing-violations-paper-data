#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

using matrix = std::vector<std::vector<std::uint32_t>>;

matrix spiral(std::size_t size);

matrix spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
