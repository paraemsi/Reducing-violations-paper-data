#include "diamond.h"

#include <stdexcept>

namespace diamond {
namespace {

// Build the diamond as a vector of strings.
// Throws std::invalid_argument if the supplied letter is not 'A'-'Z'.
std::vector<std::string> build_rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be an uppercase character A-Z");
    }

    const std::size_t n = static_cast<std::size_t>(letter - 'A') + 1;
    const std::size_t width = 2 * n - 1;

    std::vector<std::string> result;
    result.reserve(2 * n - 1);

    // Top half including the middle row.
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t padding = n - i - 1;
        std::string row(width, ' ');
        char ch = static_cast<char>('A' + i);

        row[padding] = ch;
        if (i != 0) {
            row[width - padding - 1] = ch;
        }

        result.push_back(std::move(row));
    }

    // Bottom half (mirror of the top without the middle row).
    for (std::size_t i = n - 1; i-- > 0;) {
        result.push_back(result[i]);
    }

    return result;
}

} // namespace

std::vector<std::string> rows(char letter) {
    return build_rows(letter);
}

std::string make(char letter) {
    auto lines = build_rows(letter);
    std::string output;
    for (std::size_t i = 0; i < lines.size(); ++i) {
        output += lines[i];
        if (i + 1 < lines.size()) {
            output += '\n';
        }
    }
    return output;
}

}  // namespace diamond
