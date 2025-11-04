#include "diamond.h"

namespace diamond {

namespace {
    // Lookup table avoids performing arithmetic on character codes.
    static constexpr char LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // LETTERS_LEN excludes the terminating null.
    static constexpr std::size_t LETTERS_LEN =
        (sizeof(LETTERS) / sizeof(LETTERS[0U])) - static_cast<std::size_t>(1U);
}  // namespace

[[nodiscard]] std::vector<std::string> rows(char letter) {
    // Find alphabetical index (0 for 'A', 1 for 'B', ...).
    std::size_t n = static_cast<std::size_t>(0U);
    bool found = false;
    for (std::size_t i = static_cast<std::size_t>(0U); i < LETTERS_LEN; ++i) {
        if (letter == LETTERS[i]) {
            n = i;
            found = true;
            break;
        }
    }

    if (!found) {
        // Unsupported input: return empty result.
        return std::vector<std::string>();
    }

    const std::size_t width =
        ((static_cast<std::size_t>(2U) * n) + static_cast<std::size_t>(1U));

    std::vector<std::string> result;
    result.reserve(width);

    for (std::size_t r = static_cast<std::size_t>(0U); r < width; ++r) {
        const std::size_t row_idx =
            (r <= n) ? r : (((static_cast<std::size_t>(2U) * n) - r));
        const std::size_t outer = (n - row_idx);

        std::string line(width, ' ');
        const std::size_t left = outer;
        const std::size_t right = ((width - static_cast<std::size_t>(1U)) - outer);
        const char ch = LETTERS[row_idx];

        line[left] = ch;
        line[right] = ch;

        result.emplace_back(line);
    }

    return result;
}

}  // namespace diamond
