#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <vector>

namespace spiral_matrix {

 // Return a `size`×`size` matrix filled with the numbers 1..size² in
 // clockwise spiral order. When `size` is 0 an empty matrix is returned.
std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
