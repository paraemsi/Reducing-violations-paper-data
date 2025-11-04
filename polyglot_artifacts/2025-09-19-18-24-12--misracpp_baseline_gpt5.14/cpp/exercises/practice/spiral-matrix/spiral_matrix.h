#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>

namespace spiral_matrix {

using matrix_t = std::vector<std::vector<int>>;

matrix_t spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
