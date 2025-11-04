#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstddef>

namespace spiral_matrix {

/* Return a size x size matrix filled in a clockwise spiral starting at 1 in the top-left. */
std::vector<std::vector<unsigned int> > spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
