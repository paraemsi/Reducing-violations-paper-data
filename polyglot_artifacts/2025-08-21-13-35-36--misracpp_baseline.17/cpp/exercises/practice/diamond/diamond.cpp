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
        int outer = n - i;
        int inner = i == 0 ? 0 : 2 * i;
        // Top half
        result[i][outer] = ch;
        if (i != 0) result[i][outer + inner] = ch;
        // Bottom half (mirror)
        result[size - 1 - i][outer] = ch;
        if (i != 0) result[size - 1 - i][outer + inner] = ch;
    }
    return result;
}

}  // namespace diamond
