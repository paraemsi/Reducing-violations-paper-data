#include "diamond.h"

#include <stdexcept>   // std::invalid_argument
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> generate(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be in range 'A'..'Z'");
    }

    const int radius = letter - 'A';          // distance from centre to edge
    const int size   = 2 * radius + 1;        // width == height

    std::vector<std::string> result;
    result.reserve(static_cast<std::size_t>(size));

    for (int i = 0; i < size; ++i) {
        const int idx        = (i <= radius) ? i : (2 * radius - i);
        const char ch        = static_cast<char>('A' + idx);
        const int lead_space = radius - idx;

        std::string row(static_cast<std::size_t>(size), ' ');
        row[static_cast<std::size_t>(lead_space)]                     = ch;
        row[static_cast<std::size_t>(size - 1 - lead_space)]          = ch;

        result.push_back(std::move(row));
    }

    return result;
}

std::vector<std::string> rows(char letter) {
    return generate(letter);
}

std::string generate_string(char letter) {
    const auto lines = generate(letter);
    std::string output;
    output.reserve(lines.size() * (lines.empty() ? 0 : lines.front().size() + 1));

    for (std::size_t i = 0; i < lines.size(); ++i) {
        output += lines[i];
        if (i + 1 < lines.size()) {
            output += '\n';
        }
    }
    return output;
}

}  // namespace diamond
