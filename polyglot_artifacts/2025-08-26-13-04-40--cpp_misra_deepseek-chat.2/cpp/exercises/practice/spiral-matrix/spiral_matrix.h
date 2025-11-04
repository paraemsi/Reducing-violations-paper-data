#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

// Define type aliases to avoid using standard integer types directly
using matrix_t = std::vector<std::vector<std::uint32_t>>;
using size_type = std::uint32_t;

matrix_t spiral_matrix(size_type size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
