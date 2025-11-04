#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

namespace {
    inline char to_upper_ascii(char ch) {
        return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }

    inline std::string make_row(int i, int n) {
        const int width = n * 2 + 1;
        const int leading = n - i;
        const int inner = (i == 0) ? 0 : (2 * i - 1);
        std::string row;
        row.reserve(width);

        // leading spaces
        row.append(static_cast<size_t>(leading), ' ');

        // first letter
        row.push_back(static_cast<char>('A' + i));

        if (i > 0) {
            // inner spaces + second letter
            row.append(static_cast<size_t>(inner), ' ');
            row.push_back(static_cast<char>('A' + i));
        }

        // trailing spaces to pad to width
        const int used = leading + 1 + (i > 0 ? inner + 1 : 0);
        const int trailing = width - used;
        if (trailing > 0) {
            row.append(static_cast<size_t>(trailing), ' ');
        }

        return row;
    }
}  // namespace

std::vector<std::string> rows(char letter) {
    const char upper = to_upper_ascii(letter);
    if (upper < 'A' || upper > 'Z') {
        throw std::invalid_argument("letter must be in A-Z or a-z");
    }
    const int n = upper - 'A';
    std::vector<std::string> out;
    const int height = n * 2 + 1;
    out.reserve(static_cast<size_t>(height));

    for (int i = 0; i <= n; ++i) {
        out.emplace_back(make_row(i, n));
    }
    for (int i = n - 1; i >= 0; --i) {
        out.emplace_back(make_row(i, n));
    }
    return out;
}

std::string str(char letter) {
    const auto lines = rows(letter);
    // join with '\n' without trailing newline
    std::string s;
    if (lines.empty()) return s;
    size_t total = 0;
    for (const auto& line : lines) {
        total += line.size();
    }
    total += lines.size() - 1;
    s.reserve(total);
    for (size_t i = 0; i < lines.size(); ++i) {
        if (i) s.push_back('\n');
        s += lines[i];
    }
    return s;
}

}  // namespace diamond
