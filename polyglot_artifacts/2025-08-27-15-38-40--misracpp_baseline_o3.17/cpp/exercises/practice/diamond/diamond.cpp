#include "diamond.h"
#include <string>
#include <vector>
#include <stdexcept>

namespace diamond {

// Create a diamond shape represented as a vector of strings.
// Each string has equal length (square output).
std::vector<std::string> make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be an uppercase alphabetic character");
    }

    const int n = letter - 'A';
    const int size = 2 * n + 1;              // height and width
    std::vector<std::string> lines;
    lines.reserve(size);

    auto build_row = [n, size](int row) {
        const char current = static_cast<char>('A' + row);
        const int leading = n - row;
        const int internal = (row == 0) ? 0 : 2 * row - 1;

        std::string line(size, ' ');
        line[leading] = current;
        if (internal > 0) {
            line[leading + internal + 1] = current;
        }
        return line;
    };

    // top half (including middle)
    for (int row = 0; row <= n; ++row) {
        lines.push_back(build_row(row));
    }
    // bottom half (excluding middle)
    for (int row = n - 1; row >= 0; --row) {
        lines.push_back(build_row(row));
    }

    return lines;
}

std::vector<std::string> rows(char letter) {
    return make(letter);
}

}  // namespace diamond
