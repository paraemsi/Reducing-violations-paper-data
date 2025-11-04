#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

// Value type for matrix entries (natural numbers starting at 1)
typedef std::uint32_t value_type;

// Matrix type alias
typedef std::vector<std::vector<value_type> > matrix;

 // Generate a size x size spiral matrix (clockwise, starting at 1 in the top-left)
matrix spiral(std::size_t size);

// Alternative entry-point with exercise name (to accommodate differing callers)
matrix spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
