#include "diamond.h"
#include <cctype>
#include <string>
#include <vector>

namespace diamond {

namespace {
inline std::string spaces(std::size_t n) {
    return std::string(n, ' ');
}
}  // namespace

std::vector<std::string> rows(char letter) {
    unsigned char u = static_cast<unsigned char>(letter);
    char upper = static_cast<char>(std::toupper(u));
    if (upper < 'A' || upper > 'Z') {
        return std::vector<std::string>();
    }

    int n = upper - 'A';
    int total_lines = 2 * n + 1;
    std::vector<std::string> out;
    out.reserve(static_cast<std::size_t>(total_lines));

    auto make_line = [n](int r) -> std::string {
        char c = static_cast<char>('A' + r);
        std::size_t outer = static_cast<std::size_t>(n - r);
        if (r == 0) {
            return spaces(outer) + std::string(1, 'A') + spaces(outer);
        }
        std::size_t inner = static_cast<std::size_t>(2 * r - 1);
        return spaces(outer) + std::string(1, c) + spaces(inner) + std::string(1, c) + spaces(outer);
    };

    for (int r = 0; r <= n; ++r) {
        out.push_back(make_line(r));
    }
    for (int r = n - 1; r >= 0; --r) {
        out.push_back(make_line(r));
    }

    return out;
}

std::string make(char letter) {
    auto lines = rows(letter);
    if (lines.empty()) {
        return std::string();
    }

    std::string result;
    std::size_t cap = lines.size() > 0 ? lines.size() - 1 : 0; // for newlines
    for (const auto& line : lines) {
        cap += line.size();
    }
    result.reserve(cap);

    bool first = true;
    for (const auto& line : lines) {
        if (!first) {
            result.push_back('\n');
        }
        first = false;
        result += line;
    }

    return result;
}

}  // namespace diamond
