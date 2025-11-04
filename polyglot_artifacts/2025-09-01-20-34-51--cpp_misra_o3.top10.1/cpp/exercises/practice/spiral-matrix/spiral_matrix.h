#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

/*
 * Generate a clockwise-spiral, square matrix of the requested size.
 * Each cell holds an incrementing natural number starting at 1.
 */
auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
