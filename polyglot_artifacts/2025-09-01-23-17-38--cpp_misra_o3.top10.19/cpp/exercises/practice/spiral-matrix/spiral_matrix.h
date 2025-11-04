#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

using Matrix = std::vector<std::vector<std::uint32_t>>;

auto spiral(std::uint32_t size) -> Matrix;

/* Wrapper matching the function name expected by the unit tests */
auto spiral_matrix(std::uint32_t size) -> Matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
