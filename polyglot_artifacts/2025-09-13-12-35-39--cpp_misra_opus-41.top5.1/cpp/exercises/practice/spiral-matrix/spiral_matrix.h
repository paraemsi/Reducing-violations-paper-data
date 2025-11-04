#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

using Matrix = std::vector<std::vector<unsigned int>>;

Matrix spiral_matrix(std::int32_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
