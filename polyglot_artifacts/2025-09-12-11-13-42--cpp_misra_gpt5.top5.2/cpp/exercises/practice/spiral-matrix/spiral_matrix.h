#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace spiral_matrix {

// Type alias for the spiral matrix
typedef std::vector<std::vector<std::uint32_t>> matrix_t;

// Generate a clockwise spiral matrix of the given size.
// If size == 0, returns an empty matrix.
// If size*size exceeds the range of std::uint32_t, returns an empty matrix.
matrix_t spiral(std::size_t size);

// Alternative API retained for compatibility with some callers/tests.
// Delegates to spiral(size).
matrix_t spiral_matrix(std::size_t size);

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
