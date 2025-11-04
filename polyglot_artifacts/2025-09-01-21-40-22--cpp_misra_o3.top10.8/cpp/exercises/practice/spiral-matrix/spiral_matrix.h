#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

/*  Fixed-width unsigned integer used for all matrix values */
using value_t  = std::uint32_t;
/*  Convenience alias for the 2-D spiral matrix container */
using matrix_t = std::vector<std::vector<value_t>>;

/*  Generate a clockwise spiral matrix of size `dimension` × `dimension`.
    Returns an empty matrix when `dimension` is 0. */
auto generate(std::size_t dimension) -> matrix_t;

/*  Wrapper kept for backward-compatibility with existing tests */
auto spiral_matrix(std::size_t dimension) -> matrix_t;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
