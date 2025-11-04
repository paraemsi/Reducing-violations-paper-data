#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>

namespace spiral_matrix {

// Alias for the spiral matrix container type.
using matrix_t = std::vector<std::vector<int>>;

// Returns a size x size matrix filled in a clockwise spiral starting from 1.
matrix_t generate(std::size_t size);

// Alias function with a commonly used name in some code bases.
matrix_t spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
