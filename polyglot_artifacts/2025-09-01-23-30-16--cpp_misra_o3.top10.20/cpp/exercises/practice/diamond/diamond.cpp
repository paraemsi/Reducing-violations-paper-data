#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <string>

namespace diamond {

[[nodiscard]] auto rows(char letter) -> std::vector<std::string> {
    /*  Alphabet lookup avoids arithmetic on character values and therefore
        complies with the MISRA rule forbidding use of a character’s numeric
        value. */
    constexpr std::string_view alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    const std::size_t pos{alphabet.find(letter)};
    if (pos == std::string_view::npos) {
        throw std::invalid_argument{"letter must be between 'A' and 'Z'"};
    }

    const std::size_t size{
        ((pos * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U))};

    std::vector<std::string> lines{};
    lines.reserve(size);

    const auto build_row = [pos](std::size_t idx) -> std::string {
        const std::size_t outer_spaces{pos - idx};
        const char          ch{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[idx]};

        std::string row(outer_spaces, ' ');
        row.push_back(ch);

        if (idx != static_cast<std::size_t>(0U)) {
            const std::size_t inner_spaces{
                ((idx * static_cast<std::size_t>(2U)) -
                 static_cast<std::size_t>(1U))};
            row.append(inner_spaces, ' ');
            row.push_back(ch);
        }

        row.append(outer_spaces, ' ');
        return row;
    };

    for (std::size_t idx{static_cast<std::size_t>(0U)}; idx <= pos; ++idx) {
        lines.push_back(build_row(idx));
    }

    if (pos > static_cast<std::size_t>(0U)) {
        for (std::size_t idx{pos - static_cast<std::size_t>(1U)};; --idx) {
            lines.push_back(build_row(idx));
            if (idx == static_cast<std::size_t>(0U)) {
                break;
            }
        }
    }

    return lines;
}


}  // namespace diamond
