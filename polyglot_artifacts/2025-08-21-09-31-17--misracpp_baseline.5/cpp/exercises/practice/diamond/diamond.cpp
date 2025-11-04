#include "diamond.h"

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        return {};
    }
    int n = letter - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> result(size, std::string(size, ' '));

    for (int i = 0; i <= n; ++i) {
        char ch = 'A' + i;
        int outer_spaces = n - i;

        // Top half
        result[i][outer_spaces] = ch;
        if (i != 0) {
            result[i][size - outer_spaces - 1] = ch;
        }

        // Bottom half (mirror)
        result[size - i - 1][outer_spaces] = ch;
        if (i != 0) {
            result[size - i - 1][size - outer_spaces - 1] = ch;
        }
    }
    return result;
}

}  // namespace diamond
