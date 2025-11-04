#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <vector>

namespace spiral_matrix {

//  Type alias for the returned matrix – keeps the element type explicit
//  Use explicit signed-32-bit element type to satisfy MISRA while
//  remaining compatible with the test-suite expectations.
using matrix_t = std::vector<std::vector<std::int32_t>>;

//  Return a size × size clockwise-spiral matrix filled with 1, 2, …
//  A size of 0 returns an empty matrix.
auto spiral_matrix(std::uint32_t size) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
