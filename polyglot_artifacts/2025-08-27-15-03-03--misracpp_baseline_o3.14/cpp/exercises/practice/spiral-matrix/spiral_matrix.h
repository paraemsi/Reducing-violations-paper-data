#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> generate(std::size_t size);
std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size);  // backward-compatibility alias

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
