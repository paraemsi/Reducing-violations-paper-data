#include "diamond.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

static inline char to_upper_ascii(char c) {
    if (c >= 'a' && c <= 'z') return static_cast<char>(c - 'a' + 'A');
    return c;
}

std::vector<std::string> rows(char letter) {
    char L = to_upper_ascii(letter);
    if (L < 'A' || L > 'Z') {
        throw std::invalid_argument("letter must be in range A-Z or a-z");
    }

    int n = L - 'A' + 1;
    int size = 2 * n - 1;

    std::vector<std::string> out;
    out.reserve(static_cast<size_t>(size));

    for (int i = 0; i < size; ++i) {
        int idx = i < n ? i : (size - 1 - i);
        char ch = static_cast<char>('A' + idx);

        std::string line(static_cast<size_t>(size), ' ');

        int left = (n - 1) - idx;
        int right = (n - 1) + idx;
        line[static_cast<size_t>(left)] = ch;
        line[static_cast<size_t>(right)] = ch;

        out.push_back(line);
    }

    return out;
}

std::string make_diamond(char letter) {
    auto lines = rows(letter);
    std::string result;
    if (!lines.empty()) {
        size_t total = 0;
        for (size_t i = 0; i < lines.size(); ++i) {
            total += lines[i].size();
        }
        if (lines.size() > 1) {
            total += lines.size() - 1; // newlines between rows
        }
        result.reserve(total);
        for (size_t i = 0; i < lines.size(); ++i) {
            result += lines[i];
            if (i + 1 < lines.size()) result.push_back('\n');
        }
    }
    return result;
}

}  // namespace diamond
