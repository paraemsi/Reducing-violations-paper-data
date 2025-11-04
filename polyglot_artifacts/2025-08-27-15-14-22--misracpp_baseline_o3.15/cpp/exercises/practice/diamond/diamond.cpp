#include "diamond.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::string make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be an uppercase A-Z");
    }

    const int n = letter - 'A';          // 0-based index of the supplied letter
    const int width = n * 2 + 1;         // Width (and height) of the square

    std::string result;
    result.reserve(width * width + width);  // Rough upper-bound capacity

    auto spaces = [](int count) { return std::string(static_cast<size_t>(count), ' '); };

    // Top half including the middle line
    for (int i = 0; i <= n; ++i) {
        const char c = static_cast<char>('A' + i);
        const int leading = n - i;
        const int inner = (i == 0) ? 0 : i * 2 - 1;

        result += spaces(leading);
        result += c;
        if (inner > 0) {
            result += spaces(inner);
            result += c;
        }
        result += spaces(leading);

        if (i != n) result += '\n';  // No newline after the middle line (yet)
    }

    // Bottom half (mirror of the top, excluding middle line)
    for (int i = n - 1; i >= 0; --i) {
        result += '\n';

        const char c = static_cast<char>('A' + i);
        const int leading = n - i;
        const int inner = (i == 0) ? 0 : i * 2 - 1;

        result += spaces(leading);
        result += c;
        if (inner > 0) {
            result += spaces(inner);
            result += c;
        }
        result += spaces(leading);
    }

    return result;
}

std::vector<std::string> rows(char letter) {
    std::string diamond_str = make(letter);
    std::vector<std::string> lines;
    std::size_t start = 0;
    std::size_t end;
    while ((end = diamond_str.find('\n', start)) != std::string::npos) {
        lines.emplace_back(diamond_str.substr(start, end - start));
        start = end + 1;
    }
    lines.emplace_back(diamond_str.substr(start));
    return lines;
}

}  // namespace diamond
