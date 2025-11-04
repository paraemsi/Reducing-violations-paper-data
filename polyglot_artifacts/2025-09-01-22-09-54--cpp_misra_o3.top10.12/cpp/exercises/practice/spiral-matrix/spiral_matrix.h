#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

/* Fixed-width unsigned type for matrix elements */
using matrix_t = std::vector<std::vector<std::uint32_t>>;

/* Return an n × n clockwise spiral matrix filled with 1, 2, … */
auto spiral_matrix(std::uint32_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
