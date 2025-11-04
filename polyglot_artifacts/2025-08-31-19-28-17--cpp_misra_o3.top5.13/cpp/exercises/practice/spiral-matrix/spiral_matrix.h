#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

/*
 * Build a square spiral matrix of the requested size.
 * Returns an empty matrix when size is 0.
 */
auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
