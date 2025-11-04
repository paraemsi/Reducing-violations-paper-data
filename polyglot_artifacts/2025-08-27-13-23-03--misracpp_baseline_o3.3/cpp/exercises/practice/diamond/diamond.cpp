#include "diamond.h"
#include <sstream>
#include <string>
#include <vector>

namespace diamond {

std::string make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        return "";
    }

    const int n = letter - 'A';
    std::ostringstream oss;

    // Top half including the middle row
    for (int i = 0; i <= n; ++i) {
        const char c = static_cast<char>('A' + i);
        const int leading = n - i;
        const int inner = (i == 0) ? 0 : 2 * i - 1;

        oss << std::string(leading, ' ');
        oss << c;
        if (inner > 0) {
            oss << std::string(inner, ' ');
            oss << c;
        }
        oss << std::string(leading, ' ');
        oss << '\n';
    }

    // Bottom half (excluding the middle row)
    for (int i = n - 1; i >= 0; --i) {
        const char c = static_cast<char>('A' + i);
        const int leading = n - i;
        const int inner = (i == 0) ? 0 : 2 * i - 1;

        oss << std::string(leading, ' ');
        oss << c;
        if (inner > 0) {
            oss << std::string(inner, ' ');
            oss << c;
        }
        oss << std::string(leading, ' ');
        if (i != 0) {  // no trailing newline on the very last line
            oss << '\n';
        }
    }

    std::string result = oss.str();
    if (!result.empty() && result.back() == '\n') {  // remove trailing newline
        result.pop_back();
    }
    return result;
}

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    if (letter < 'A' || letter > 'Z') {
        return result;
    }

    const int n = letter - 'A';

    auto build_row = [n](int i) {
        const char c = static_cast<char>('A' + i);
        const int leading = n - i;
        const int inner = (i == 0) ? 0 : 2 * i - 1;

        std::string row;
        row.append(leading, ' ');
        row.push_back(c);
        if (inner > 0) {
            row.append(inner, ' ');
            row.push_back(c);
        }
        row.append(leading, ' ');
        return row;
    };

    // Top half including middle
    for (int i = 0; i <= n; ++i) {
        result.push_back(build_row(i));
    }
    // Bottom half excluding middle
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(build_row(i));
    }

    return result;
}

}  // namespace diamond
