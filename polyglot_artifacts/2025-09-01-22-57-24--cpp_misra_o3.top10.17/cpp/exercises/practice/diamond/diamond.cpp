#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

auto rows(char letter) -> std::vector<std::string>
{
    static const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    // Ensure the requested letter exists within the allowed range.
    const std::string::size_type pos{alphabet.find(letter)};
    if (pos == std::string::npos) {
        throw std::invalid_argument("Letter must be an upper-case character between 'A' and 'Z'.");
    }

    const std::size_t height{(static_cast<std::size_t>(pos) * static_cast<std::size_t>(2U))
                             + static_cast<std::size_t>(1U)};
    std::vector<std::string> result{};
    result.reserve(height);

    // Build the top half including the middle row.
    for (std::size_t i{static_cast<std::size_t>(0U)}; i <= static_cast<std::size_t>(pos); ++i) {
        const char current{alphabet[static_cast<std::string::size_type>(i)]};

        const std::size_t leading{static_cast<std::size_t>(pos) - i};
        const std::size_t internal{(i == static_cast<std::size_t>(0U))
                                       ? static_cast<std::size_t>(0U)
                                       : ((i * static_cast<std::size_t>(2U))
                                          - static_cast<std::size_t>(1U))};

        std::string line{};
        line.append(leading, ' ');
        line.push_back(current);
        if (internal != static_cast<std::size_t>(0U)) {
            line.append(internal, ' ');
            line.push_back(current);
        }
        line.append(leading, ' ');
        result.push_back(line);
    }

    // Mirror the upper half (excluding the middle) to obtain the bottom half.
    for (std::size_t i{static_cast<std::size_t>(pos)}; i > static_cast<std::size_t>(0U); --i) {
        result.push_back(result[i - static_cast<std::size_t>(1U)]);
    }

    return result;
}

}  // namespace diamond
