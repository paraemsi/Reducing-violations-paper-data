#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <vector>

namespace spiral_matrix {

// Returns a size x size clockwise spiral matrix filled with 1..size*size.
std::vector<std::vector<int>> spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
