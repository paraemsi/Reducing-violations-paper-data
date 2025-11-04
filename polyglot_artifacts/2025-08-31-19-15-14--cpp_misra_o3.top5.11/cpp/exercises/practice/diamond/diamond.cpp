#include "diamond.h"

#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] auto make_diamond(char const letter) -> std::vector<std::string>
{
    /* Alphabet used to look-up characters without relying on
       arithmetic or relational ordering on character values. */
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    const std::size_t pos{alphabet.find(letter)};
    if (pos == std::string::npos) {
        /* Unsupported input – return an empty result. */
        return {};
    }

    const std::size_t size{
        (pos * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U)};

    std::vector<std::string> lines{};
    lines.reserve(size);

    for (std::size_t row{static_cast<std::size_t>(0U)}; row < size; ++row) {
        const std::size_t idx{(row <= pos)
                                  ? row
                                  : ((size - static_cast<std::size_t>(1U)) - row)};
        const std::size_t outer_spaces{pos - idx};
        const std::size_t inner_spaces{(idx == static_cast<std::size_t>(0U))
                                           ? static_cast<std::size_t>(0U)
                                           : ((idx * static_cast<std::size_t>(2U)) -
                                              static_cast<std::size_t>(1U))};

        std::string line(outer_spaces, ' ');
        line.push_back(alphabet[idx]);

        if (inner_spaces > static_cast<std::size_t>(0U)) {
            line.append(inner_spaces, ' ');
            line.push_back(alphabet[idx]);
        }

        line.append(outer_spaces, ' ');
        lines.emplace_back(std::move(line));
    }

    return lines;
}

/* Forwarder required by the public interface – keeps the implementation
   in one place. */
[[nodiscard]] auto rows(char const letter) -> std::vector<std::string>
{
    return make_diamond(letter);
}

}  // namespace diamond
