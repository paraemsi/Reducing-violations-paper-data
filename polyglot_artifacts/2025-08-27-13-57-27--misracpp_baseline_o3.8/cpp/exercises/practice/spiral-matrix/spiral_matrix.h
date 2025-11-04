#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>  // for std::size_t

namespace spiral_matrix {

using matrix_t = std::vector<std::vector<unsigned int>>;
/**
 * Generate a square matrix of the given size filled in a clockwise
 * spiral pattern starting at 1 in the top-left corner.
 *
 * Example size = 3
 *  1 2 3
 *  8 9 4
 *  7 6 5
 *
 * @param size length of one side of the square matrix
 * @return matrix_t the resulting spiral matrix
 */
matrix_t spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
