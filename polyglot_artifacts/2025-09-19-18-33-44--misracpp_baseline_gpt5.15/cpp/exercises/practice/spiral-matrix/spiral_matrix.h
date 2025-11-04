#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <vector>

namespace spiral_matrix {

/**
 * Returns a size x size matrix filled in clockwise spiral order starting at 1.
 * If size is 0, returns an empty matrix.
 */

// Alias for compatibility with call sites expecting this name.
std::vector<std::vector<int>> spiral_matrix(std::size_t size);


}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
