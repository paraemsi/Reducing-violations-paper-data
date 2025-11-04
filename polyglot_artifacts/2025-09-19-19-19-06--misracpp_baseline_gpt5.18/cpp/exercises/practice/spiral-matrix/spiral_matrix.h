#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <vector>

namespace spiral_matrix {

#if __cplusplus >= 201103L
using matrix = std::vector<std::vector<int>>;
#else
typedef std::vector<std::vector<int> > matrix;
#endif

// Build a size x size matrix filled 1..size*size in a clockwise spiral.
matrix spiral(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
