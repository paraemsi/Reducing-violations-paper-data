#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

using matrix_size_t = ::std::uint32_t;
using matrix_value_t = ::std::uint32_t;
using matrix_t = ::std::vector< ::std::vector<matrix_value_t> >;

// Returns a square matrix of the given size, filled in a clockwise spiral with natural numbers starting from 1.
matrix_t spiral_matrix(matrix_size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
