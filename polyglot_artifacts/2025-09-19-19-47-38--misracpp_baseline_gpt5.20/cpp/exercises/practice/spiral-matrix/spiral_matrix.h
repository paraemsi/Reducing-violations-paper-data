#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <vector>

namespace spiral_matrix {

 // Generate a size x size spiral matrix filled clockwise starting at 1
std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
