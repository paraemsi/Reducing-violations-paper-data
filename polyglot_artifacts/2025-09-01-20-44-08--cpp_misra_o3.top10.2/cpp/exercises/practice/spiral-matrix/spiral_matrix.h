#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

using value_t  = std::uint32_t;                                       /* fixed-width unsigned integral alias */
using matrix_t = std::vector<std::vector<value_t>>;                   /* 2-D matrix of value_t values */
matrix_t spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
