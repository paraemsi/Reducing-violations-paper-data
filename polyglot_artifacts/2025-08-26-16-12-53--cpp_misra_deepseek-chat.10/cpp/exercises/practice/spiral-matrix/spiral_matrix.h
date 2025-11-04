#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

using int32 = std::int32_t;

std::vector<std::vector<int32>> spiral_matrix(int32 size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
