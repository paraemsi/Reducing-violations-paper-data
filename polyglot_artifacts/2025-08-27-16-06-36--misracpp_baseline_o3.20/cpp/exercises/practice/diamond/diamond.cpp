#include "diamond.h"
#include <string>
#include <vector>
#include <stdexcept>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    // Re-use the already-tested `rows` helper to avoid duplicating logic.
    const std::vector<std::string> lines = rows(letter);

    return lines;
}

std::string make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int n = letter - 'A';
    const int size = 2 * n + 1;
    std::vector<std::string> lines;
    lines.reserve(size);

    auto line_for = [n](int idx) -> std::string {
        char ch = static_cast<char>('A' + idx);
        int leading = n - idx;
        int internal = (idx == 0) ? 0 : 2 * idx - 1;

        std::string line;
        line.append(leading, ' ');
        line.push_back(ch);
        if (internal > 0) {
            line.append(internal, ' ');
            line.push_back(ch);
        }
        line.append(leading, ' ');
        return line;
    };

    for (int i = 0; i <= n; ++i) {
        lines.emplace_back(line_for(i));
    }
    for (int i = n - 1; i >= 0; --i) {
        lines.emplace_back(line_for(i));
    }

    std::string result;
    for (size_t i = 0; i < lines.size(); ++i) {
        result += lines[i];
        if (i + 1 < lines.size()) {
            result.push_back('\n');
        }
    }
    return result;
}

}  // namespace diamond
