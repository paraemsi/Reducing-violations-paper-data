#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

namespace {
std::string build_row(char c, int row_index, int n) {
    // n = number of letters from 'A' to the widest letter (inclusive)
    const int outer = n - 1 - row_index;
    const int inner = row_index == 0 ? 0 : 2 * row_index - 1;
    const int width = 2 * n - 1;

    std::string line;
    line.reserve(width);
    line.append(outer, ' ');
    if (row_index == 0) {
        line.push_back('A');
    } else {
        line.push_back(c);
        line.append(inner, ' ');
        line.push_back(c);
    }
    line.append(outer, ' ');
    return line;
}
}  // namespace

std::vector<std::string> rows(char letter) {
    unsigned char uc = static_cast<unsigned char>(letter);
    char upper = static_cast<char>(std::toupper(uc));
    if (upper < 'A' || upper > 'Z') {
        throw std::invalid_argument("letter must be in range 'A'..'Z' (case-insensitive)");
    }

    const int n = upper - 'A' + 1;
    const int height = 2 * n - 1;

    std::vector<std::string> top;
    top.reserve(n);
    for (int i = 0; i < n; ++i) {
        char c = static_cast<char>('A' + i);
        top.emplace_back(build_row(c, i, n));
    }

    std::vector<std::string> lines;
    lines.reserve(height);
    for (int i = 0; i < n; ++i) lines.emplace_back(top[i]);
    for (int i = n - 2; i >= 0; --i) lines.emplace_back(top[i]);

    return lines;
}

std::string make(char letter) {
    const auto lines = rows(letter);
    // Join with newline, no trailing newline at the end
    std::string out;
    // Pre-reserve approximate size: width * height + (height - 1)
    const std::size_t height = lines.size();
    const std::size_t width = height ? lines[0].size() : 0;
    out.reserve(width * height + (height > 0 ? height - 1 : 0));
    for (std::size_t i = 0; i < lines.size(); ++i) {
        out += lines[i];
        if (i + 1 < lines.size()) out += '\n';
    }
    return out;
}

}  // namespace diamond
