#include "diamond.h"

#include <cstdint>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace diamond {

[[nodiscard]] auto rows(char letter) -> std::vector<std::string>
{
    static const std::string alphabet{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

    /* Find the position of the requested letter. */
    const std::size_t pos_raw{ alphabet.find(letter) };
    if (pos_raw == std::string::npos) {
        /* Invalid input – return an empty diamond. */
        return {};
    }

    const std::size_t idx{ pos_raw };
    const std::size_t side{ (idx * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U) };

    std::vector<std::string> rows{};
    rows.reserve(side);

    for (std::size_t row{ static_cast<std::size_t>(0U) }; row < side; ++row) {
        const std::size_t eff_row{
            (row <= idx) ? row : (side - static_cast<std::size_t>(1U) - row)
        };
        const std::size_t leading{
            idx - eff_row
        };
        const std::size_t internal{
            (eff_row == static_cast<std::size_t>(0U))
                ? static_cast<std::size_t>(0U)
                : (((eff_row * static_cast<std::size_t>(2U)) - static_cast<std::size_t>(1U)))
        };

        std::string line{};
        line.reserve(side);

        line.append(leading, ' ');
        line.push_back(alphabet[eff_row]);

        if (internal > static_cast<std::size_t>(0U)) {
            line.append(internal, ' ');
            line.push_back(alphabet[eff_row]);
        }

        line.append(leading, ' ');
        rows.emplace_back(std::move(line));
    }

    return rows;
}

}  // namespace diamond
