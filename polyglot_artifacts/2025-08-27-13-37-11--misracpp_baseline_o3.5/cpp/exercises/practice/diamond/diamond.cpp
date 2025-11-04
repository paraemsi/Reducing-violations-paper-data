#include "diamond.h"

#include <stdexcept>
#include <sstream>
#include <vector>

namespace diamond {

std::string generate(char letter) {
    // Build each line via rows() and join them with newline characters.
    const auto lines = rows(letter);

    std::ostringstream oss;
    for (std::size_t i = 0; i < lines.size(); ++i) {
        if (i != 0) {
            oss << '\n';
        }
        oss << lines[i];
    }
    return oss.str();
}

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int n = letter - 'A';  // 0-based index of the supplied letter
    std::vector<std::string> out;

    // Helper to build a single line of the diamond.
    auto make_line = [n](int idx) {
        const int leading  = n - idx;          // Leading/trailing spaces
        const int internal = idx == 0 ? 0
                                      : 2 * idx - 1;

        std::string line;
        line.append(leading, ' ');

        const char c = static_cast<char>('A' + idx);
        line.push_back(c);

        if (internal > 0) {
            line.append(internal, ' ');
            line.push_back(c);
        }

        line.append(leading, ' ');
        return line;
    };

    // Top half including centre
    for (int i = 0; i <= n; ++i) {
        out.push_back(make_line(i));
    }
    // Bottom half
    for (int i = n - 1; i >= 0; --i) {
        out.push_back(make_line(i));
    }
    return out;
}

}  // namespace diamond
