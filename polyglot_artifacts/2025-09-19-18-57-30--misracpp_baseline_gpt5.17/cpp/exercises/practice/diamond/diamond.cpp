#include "diamond.h"

#include <cctype>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Normalize to uppercase ASCII letter
    unsigned char uc = static_cast<unsigned char>(letter);
    char end = static_cast<char>(std::toupper(uc));
    if (end < 'A' || end > 'Z') {
        return {};
    }

    int n = end - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> result;
    result.reserve(size);

    auto make_row = [&](int i) {
        std::string row(size, ' ');
        int outer = n - i;
        char ch = static_cast<char>('A' + i);
        row[outer] = ch;
        if (i > 0) {
            row[size - outer - 1] = ch;
        }
        return row;
    };

    for (int i = 0; i <= n; ++i) {
        result.push_back(make_row(i));
    }
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(make_row(i));
    }

    return result;
}

}  // namespace diamond
