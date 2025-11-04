#include "diamond.h"

#include <stdexcept>
#include <vector>

namespace diamond {

namespace {

// Helper to create a single row of the diamond given
// the row index i (0 == A, 1 == B, …, n == target letter)
std::string make_row(int i, int n) {
    const int width = 2 * n + 1;          // width == height
    const char ch  = static_cast<char>('A' + i);

    std::string row(width, ' ');

    const int leading = n - i;
    row[leading] = ch;                     // left letter

    if (i != 0) {
        const int right = width - leading - 1;
        row[right] = ch;                   // right letter
    }

    return row;
}

} // namespace

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int n = letter - 'A';
    std::vector<std::string> result;
    result.reserve(2 * n + 1);

    // top half (including middle row)
    for (int i = 0; i <= n; ++i) {
        result.push_back(make_row(i, n));
    }

    // bottom half (excluding middle row)
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(make_row(i, n));
    }

    return result;
}

}  // namespace diamond
