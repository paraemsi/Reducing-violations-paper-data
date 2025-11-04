#include "diamond.h"

#include <cctype>
#include <string>
#include <vector>

namespace diamond {

static std::string spaces(std::size_t count) {
    return std::string(count, ' ');
}

std::vector<std::string> rows(char letter) {
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (upper < 'A' || upper > 'Z') {
        return {};
    }

    int idx = upper - 'A';
    int width = 2 * idx + 1;
    int height = width;

    std::vector<std::string> out;
    out.reserve(static_cast<std::size_t>(height));

    // Build top half including middle row
    for (int i = 0; i <= idx; ++i) {
        char ch = static_cast<char>('A' + i);
        int leading = idx - i;
        std::string line;
        line.reserve(static_cast<std::size_t>(width));
        if (i == 0) {
            line = spaces(static_cast<std::size_t>(leading)) + ch + spaces(static_cast<std::size_t>(leading));
        } else {
            int inner = 2 * i - 1;
            line = spaces(static_cast<std::size_t>(leading)) + ch + spaces(static_cast<std::size_t>(inner)) + ch + spaces(static_cast<std::size_t>(leading));
        }
        out.push_back(std::move(line));
    }

    // Build bottom half excluding middle row
    for (int i = idx - 1; i >= 0; --i) {
        out.push_back(out[static_cast<std::size_t>(i)]);
    }

    return out;
}

std::string make(char letter) {
    auto lines = rows(letter);
    if (lines.empty()) {
        return std::string();
    }

    std::string result;
    // Reserve total size of all lines plus newlines between them
    std::size_t total = 0;
    for (const auto& l : lines) total += l.size();
    if (!lines.empty()) total += lines.size() - 1;
    result.reserve(total);

    for (std::size_t i = 0; i < lines.size(); ++i) {
        if (i) result += '\n';
        result += lines[i];
    }
    return result;
}

}  // namespace diamond
