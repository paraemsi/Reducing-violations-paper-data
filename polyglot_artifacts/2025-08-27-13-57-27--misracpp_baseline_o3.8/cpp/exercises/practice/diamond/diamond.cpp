#include "diamond.h"

#include <sstream>
#include <stdexcept>
#include <vector>

namespace diamond {

std::string make_diamond(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int max_idx = letter - 'A';          // 0-based index of widest row
    const int size    = max_idx * 2 + 1;       // width == height of diamond

    std::ostringstream out;

    for (int row = 0; row < size; ++row) {
        const int idx           = row <= max_idx ? row : 2 * max_idx - row;
        const char current_char = static_cast<char>('A' + idx);

        const int leading_spaces = max_idx - idx;
        const int inner_spaces   = idx == 0 ? 0 : idx * 2 - 1;

        // leading spaces
        out << std::string(leading_spaces, ' ');
        // first letter
        out << current_char;

        if (inner_spaces > 0) {
            // middle spaces and second letter
            out << std::string(inner_spaces, ' ') << current_char;
        }

        // trailing spaces (same count as leading)
        out << std::string(leading_spaces, ' ');

        out << '\n';
    }

    return out.str();
}

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int max_idx = letter - 'A';
    const int size    = max_idx * 2 + 1;

    std::vector<std::string> result;
    result.reserve(size);

    for (int row = 0; row < size; ++row) {
        const int idx           = row <= max_idx ? row : 2 * max_idx - row;
        const char current_char = static_cast<char>('A' + idx);

        const int leading_spaces = max_idx - idx;
        const int inner_spaces   = idx == 0 ? 0 : idx * 2 - 1;

        std::string line;
        line.append(leading_spaces, ' ');
        line.push_back(current_char);

        if (inner_spaces > 0) {
            line.append(inner_spaces, ' ');
            line.push_back(current_char);
        }

        line.append(leading_spaces, ' ');

        result.push_back(std::move(line));
    }

    return result;
}

}  // namespace diamond
