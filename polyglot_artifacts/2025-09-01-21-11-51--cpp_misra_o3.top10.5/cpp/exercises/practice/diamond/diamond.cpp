#include "diamond.h"

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <utility>

namespace diamond {

[[nodiscard]] auto rows(char letter) -> std::vector<std::string>
{
    constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr std::string_view letters(alphabet);

    const std::size_t pos{letters.find(letter)};
    if (pos == std::string_view::npos) {
        return std::vector<std::string>{};
    }

    const std::size_t size{(pos * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U)};
    std::vector<std::string> rows{};
    rows.reserve(size);

    for (std::size_t i{0U}; i <= pos; ++i) {
        const std::size_t leading{pos - i};
        const char        row_char{letters[i]};

        std::string row(leading, ' ');
        row += row_char;

        if (i != static_cast<std::size_t>(0U)) {
            const std::size_t internal{(i * static_cast<std::size_t>(2U)) - static_cast<std::size_t>(1U)};
            row += std::string(internal, ' ');
            row += row_char;
        }

        row += std::string(leading, ' ');
        rows.push_back(std::move(row));
    }

    for (std::size_t i{pos}; (i-- > static_cast<std::size_t>(0U));) {
        rows.push_back(rows[i]);
    }

    return rows;
}

[[nodiscard]] auto make(char letter) -> std::string
{
    const auto row_vec{rows(letter)};
    if (row_vec.empty()) {
        return std::string{};
    }

    std::string result{};
    for (std::size_t idx{0U}; idx < row_vec.size(); ++idx) {
        result += row_vec[idx];
        if ((idx + static_cast<std::size_t>(1U)) < row_vec.size()) {
            result += '\n';
        }
    }
    return result;
}

}  // namespace diamond
