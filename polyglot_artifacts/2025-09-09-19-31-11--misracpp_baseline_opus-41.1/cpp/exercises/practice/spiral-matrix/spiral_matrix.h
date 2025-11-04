#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>

namespace spiral_matrix {

using Matrix = std::vector<std::vector<int>>;

Matrix spiral_matrix(int size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
