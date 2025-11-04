#include "diamond.h"
#include <cctype>

namespace diamond {

std::vector<std::string> rows(char letter) {
    char ch = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (ch < 'A' || ch > 'Z') {
        return {};
    }

    const int n = ch - 'A' + 1;
    const int width = 2 * n - 1;

    std::vector<std::string> result;
    result.reserve(2 * n - 1);

    auto make_row = [n, width](int i) {
        std::string row(width, ' ');
        const int left = n - 1 - i;
        const int right = n - 1 + i;
        const char c = static_cast<char>('A' + i);
        row[left] = c;
        if (left != right) {
            row[right] = c;
        }
        return row;
    };

    for (int i = 0; i < n; ++i) {
        result.push_back(make_row(i));
    }
    for (int i = n - 2; i >= 0; --i) {
        result.push_back(make_row(i));
    }

    return result;
}

}  // namespace diamond
