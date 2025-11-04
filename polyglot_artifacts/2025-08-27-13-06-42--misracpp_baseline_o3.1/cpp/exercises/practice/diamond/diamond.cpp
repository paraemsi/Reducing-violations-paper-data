#include "diamond.h"

#include <stdexcept>
#include <vector>

namespace diamond {

/* Build diamond rows (strings without trailing newline) */
std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int radius = letter - 'A';
    const int line_length = radius * 2 + 1;

    std::vector<std::string> result;
    result.reserve(radius * 2 + 1);

    auto build_line = [&](int row) -> std::string {
        const char ch = static_cast<char>('A' + row);
        const int padding = radius - row;
        const int inner_spaces = row == 0 ? 0 : row * 2 - 1;

        std::string line;
        line.reserve(line_length);
        line.append(padding, ' ');
        line.push_back(ch);
        if (inner_spaces) {
            line.append(inner_spaces, ' ');
            line.push_back(ch);
        }
        line.append(padding, ' ');
        return line;
    };

    for (int row = 0; row <= radius; ++row) {
        result.push_back(build_line(row));
    }
    for (int row = radius - 1; row >= 0; --row) {
        result.push_back(build_line(row));
    }
    return result;
}

std::string make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    // Delegate to rows() to build the string; keeps the logic in one place.
    const auto vec = rows(letter);
    std::string result;
    result.reserve(vec.size() * (vec.empty() ? 0 : vec.front().size() + 1));
    for (std::size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i + 1 != vec.size()) {
            result.push_back('\n');
        }
    }
    return result;
}

}  // namespace diamond
