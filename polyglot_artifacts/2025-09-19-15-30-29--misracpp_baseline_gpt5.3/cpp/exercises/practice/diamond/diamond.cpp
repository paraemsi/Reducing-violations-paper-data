#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
    char ch = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (ch < 'A' || ch > 'Z') {
        throw std::invalid_argument("make_diamond: letter must be in range A-Z");
    }

    int n = ch - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> result;
    result.reserve(static_cast<size_t>(size));

    auto make_line = [n](int i) -> std::string {
        int leading = n - i;
        std::string line;
        line.reserve(static_cast<size_t>(2 * n + 1));

        line.append(static_cast<size_t>(leading), ' ');

        char c = static_cast<char>('A' + i);
        if (i == 0) {
            line.push_back(c);
        } else {
            line.push_back(c);
            int inner = 2 * i - 1;
            line.append(static_cast<size_t>(inner), ' ');
            line.push_back(c);
        }

        // no trailing spaces appended; tests expect ragged right
        return line;
    };

    for (int i = 0; i <= n; ++i) {
        result.emplace_back(make_line(i));
    }
    for (int i = n - 1; i >= 0; --i) {
        result.emplace_back(make_line(i));
    }

    return result;
}

std::string make_diamond(char letter) {
    // Build from rows() to keep a single source of truth
    const auto lines = rows(letter);
    std::string result;
    if (lines.empty()) return result;

    // Reserve approximate size (sum of line lengths + newlines)
    size_t total = 0;
    for (const auto& s : lines) total += s.size();
    result.reserve(total + lines.size() - 1);

    for (size_t i = 0; i < lines.size(); ++i) {
        if (i > 0) result.push_back('\n');
        result += lines[i];
    }
    return result;
}

}  // namespace diamond
