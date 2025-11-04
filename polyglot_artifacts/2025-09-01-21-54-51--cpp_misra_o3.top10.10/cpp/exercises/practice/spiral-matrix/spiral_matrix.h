#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {

/* Generate a size × size clockwise spiral matrix starting from 1 in the
 * top-left corner.
 *
 * When size == 0 the returned std::vector is empty.
 */
std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
