#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

typedef std::uint32_t matrix_size_t;
typedef std::uint32_t matrix_value_t;
typedef std::vector<std::vector<matrix_value_t>> matrix_t;

// Returns a square matrix of the given size, filled in spiral order.
matrix_t spiral_matrix(matrix_size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
