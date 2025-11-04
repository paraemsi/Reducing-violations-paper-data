#include "diamond.h"
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <vector>
#include <string>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (!std::isalpha(static_cast<unsigned char>(letter))) {
        throw std::invalid_argument("Input must be a letter A-Z or a-z");
    }
    letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("Letter must be between A and Z");
    }

    const int n = letter - 'A';
    const int width = 2 * n + 1;

    std::vector<std::string> result;
    result.reserve(2 * n + 1);

    auto build_row = [&](int i) -> std::string {
        int lead = n - i;
        char c = static_cast<char>('A' + i);
        std::string row;
        row.reserve(width);

        row.append(lead, ' ');
        row.push_back(c);
        if (c != 'A') {
            int inner = i * 2 - 1;
            row.append(inner, ' ');
            row.push_back(c);
        }
        row.append(lead, ' ');
        return row;
    };

    for (int i = 0; i <= n; ++i) {
        result.emplace_back(build_row(i));
    }
    for (int i = n - 1; i >= 0; --i) {
        result.emplace_back(build_row(i));
    }

    return result;
}

std::string make(char letter) {
    if (!std::isalpha(static_cast<unsigned char>(letter))) {
        throw std::invalid_argument("Input must be a letter A-Z or a-z");
    }
    letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("Letter must be between A and Z");
    }

    const int n = letter - 'A';

    std::ostringstream oss;

    auto build_row = [&](int i) {
        int lead = n - i;
        char c = static_cast<char>('A' + i);
        oss << std::string(lead, ' ');
        oss << c;
        if (c != 'A') {
            int inner = i * 2 - 1;
            oss << std::string(inner, ' ') << c;
        }
        oss << std::string(lead, ' ');
    };

    for (int i = 0; i <= n; ++i) {
        build_row(i);
        oss << '\n';
    }
    for (int i = n - 1; i >= 0; --i) {
        build_row(i);
        if (i != 0) {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace diamond
