#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

namespace {

/**
 * @brief Obtain the zero-based alphabetical index of the supplied letter.
 *
 * Uses equality comparisons only, respecting MISRA rules on character values.
 */
auto letter_index(char letter) -> std::int32_t
{
    constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (std::int32_t idx{0}; alphabet[static_cast<std::size_t>(idx)] != '\0'; ++idx) {
        if (alphabet[static_cast<std::size_t>(idx)] == letter) {
            return idx;
        }
    }

    throw std::invalid_argument("letter must be between 'A' and 'Z'");
}

/**
 * @brief Build a single line of the diamond.
 *
 * The caller guarantees 0 ≤ row ≤ 2 × index_max.
 */
auto build_line(std::int32_t index_max, std::int32_t row) -> std::string
{
    const std::int32_t spacing{
        (row <= index_max) ? (index_max - row) : (row - index_max)};

    const std::int32_t level{(index_max - spacing)};
    const std::int32_t inner_count{
        ((level > 0) ? ((level * 2) - 1) : 0)};

    constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char line_letter{alphabet[static_cast<std::size_t>(
        (row <= index_max) ? row : ((index_max * 2) - row))]};

    std::string line{};
    line.append(static_cast<std::size_t>(spacing), ' ');
    line.push_back(line_letter);

    if (inner_count > 0) {
        line.append(static_cast<std::size_t>(inner_count), ' ');
        line.push_back(line_letter);
    }

    line.append(static_cast<std::size_t>(spacing), ' ');

    return line;
}

}  // namespace

auto rows(char letter) -> std::vector<std::string>
{
    /* Validate letter and obtain its alphabetical index */
    const std::int32_t idx_max{letter_index(letter)};
    const std::int32_t height{(idx_max * 2) + 1};

    /* Pre-allocate result container */
    std::vector<std::string> lines{};
    lines.reserve(static_cast<std::size_t>(height));

    /* Build each row using the helper that honours spacing rules */
    for (std::int32_t row{0}; row < height; ++row) {
        lines.emplace_back(build_line(idx_max, row));
    }

    return lines;
}

auto make_diamond(char letter) -> std::string
{
    const std::int32_t idx_max{letter_index(letter)};
    const std::int32_t height{(idx_max * 2) + 1};

    std::vector<std::string> lines;
    lines.reserve(static_cast<std::size_t>(height));

    for (std::int32_t row{0}; row < height; ++row) {
        lines.emplace_back(build_line(idx_max, row));
    }

    std::string result{};
    for (std::size_t i{0U}; i < lines.size(); ++i) {
        result += lines[i];
        if (i + 1U < lines.size()) {
            result += '\n';
        }
    }

    return result;
}

}  // namespace diamond
