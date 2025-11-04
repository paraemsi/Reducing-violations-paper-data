#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>

namespace spiral_matrix {

 // Returns a size x size spiral matrix filled clockwise starting from 1.
std::vector<std::vector<int>> spiral(std::size_t size);
std::vector<std::vector<int>> spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
