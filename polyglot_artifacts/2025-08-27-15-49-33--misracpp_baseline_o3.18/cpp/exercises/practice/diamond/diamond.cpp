#include "diamond.h"

#include <stdexcept>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int size = letter - 'A' + 1;      // number of rows in the top half
    const int width = 2 * size - 1;         // total width/height of the square
    std::vector<std::string> rows;
    rows.reserve(static_cast<std::size_t>(width));

    auto build_row = [&](int idx) {
        // idx: 0 for 'A', 1 for 'B', ..., size-1 for `letter`
        char c = static_cast<char>('A' + idx);
        int leading = size - 1 - idx;
        std::string row(width, ' ');

        row[leading] = c;
        if (idx != 0) {
            int inner_gap = 2 * idx - 1;
            row[leading + inner_gap + 1] = c;
        }
        return row;
    };

    // Top half (including middle line)
    for (int i = 0; i < size; ++i) {
        rows.push_back(build_row(i));
    }
    // Bottom half (excluding middle line)
    for (int i = size - 2; i >= 0; --i) {
        rows.push_back(build_row(i));
    }
    return rows;
}

}  // namespace diamond
