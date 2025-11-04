#include "diamond.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // accept only uppercase ASCII letters
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int distance = letter - 'A';      // 0 for 'A', 1 for 'B', …
    const int width    = distance * 2 + 1;  // overall width / height
    const int center   = distance;          // index of the vertical axis

    // Helper to build a single row.
    auto build_row = [width, center](char ch, int offset) {
        std::string row(static_cast<std::size_t>(width), ' ');
        row[center - offset] = ch;
        row[center + offset] = ch;
        return row;
    };

    std::vector<std::string> rows;
    rows.reserve(static_cast<std::size_t>(width));

    // Top half (including the middle row)
    for (int i = 0; i <= distance; ++i) {
        rows.emplace_back(build_row(static_cast<char>('A' + i), i));
    }
    // Bottom half (excluding the middle row)
    for (int i = distance - 1; i >= 0; --i) {
        rows.emplace_back(build_row(static_cast<char>('A' + i), i));
    }

    return rows;
}

}  // namespace diamond
