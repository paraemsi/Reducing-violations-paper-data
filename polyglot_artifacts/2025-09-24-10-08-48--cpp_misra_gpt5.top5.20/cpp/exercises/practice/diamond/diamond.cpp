#include "diamond.h"

namespace diamond {

namespace {
constexpr char UPPER_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
constexpr char LOWER_ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

std::uint32_t index_in_alphabet(char ch)
{
    for (std::uint32_t i = 0U; i < 26U; ++i) {
        if ((ch == UPPER_ALPHABET[i]) || (ch == LOWER_ALPHABET[i])) {
            return i;
        }
    }
    return 26U;  // sentinel: not found
}
}  // namespace

std::vector<std::string> make(char letter)
{
    const std::uint32_t not_found = 26U;
    const std::uint32_t idx = index_in_alphabet(letter);
    if (idx == not_found) {
        return {};
    }

    const std::uint32_t one = 1U;
    const std::uint32_t two = 2U;
    const std::uint32_t width = (idx * two) + one;

    std::vector<std::string> lines;
    lines.reserve(width);

    for (std::uint32_t row = 0U; row < width; ++row) {
        std::string line(width, ' ');

        std::uint32_t top_idx = row;
        if (row > idx) {
            top_idx = ((width - one) - row);
        }

        const char current = UPPER_ALPHABET[top_idx];
        const std::uint32_t center = idx;

        if (top_idx == 0U) {
            line[center] = current;
        } else {
            const std::uint32_t left = center - top_idx;
            const std::uint32_t right = center + top_idx;
            line[left] = current;
            line[right] = current;
        }

        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> rows(char letter)
{
    return make(letter);
}

}  // namespace diamond
