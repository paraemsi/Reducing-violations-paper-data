#include "diamond.h"

#include <algorithm> // for std::max, std::transform
#include <iterator>  // for std::back_inserter
#include <numeric>   // for std::accumulate

namespace diamond {

auto generate(char letter) -> std::vector<std::string>
{
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const std::size_t pos{alphabet.find(letter)};

    /* Sanity check: if the letter is not found, return empty result. */
    if (pos == std::string::npos) {
        return {};
    }

    const std::size_t max_index{pos};
    const std::size_t width{(max_index * 2U) + 1U};

    std::vector<std::string> result{};
    result.reserve(static_cast<std::size_t>(width));

    /* Build the top half (including centre line). */
    for (std::size_t idx{0U}; idx <= max_index; ++idx) {
        const std::size_t leading{max_index - idx};
        const std::size_t inner{(idx == 0U) ? 0U : ((idx * 2U) - 1U)};

        std::string line(static_cast<std::size_t>(leading), ' ');
        line += alphabet[static_cast<std::size_t>(idx)];

        if (idx > 0U) {
            line.append(static_cast<std::size_t>(inner), ' ');
            line += alphabet[static_cast<std::size_t>(idx)];
        }

        line.append(static_cast<std::size_t>(leading), ' ');
        result.emplace_back(std::move(line));
    }

    /* Mirror the top half (excluding centre) to form the bottom half. */
    for (std::size_t idx{max_index}; idx-- > 0U;) {
        result.emplace_back(result[idx]);
    }

    return result;
}

auto rows(char letter) -> std::vector<std::string>
{
    /* Forward to the primary implementation. */
    return generate(letter);
}

auto to_string(const std::vector<std::string>& lines) -> std::string
{
    if (lines.empty()) {
        return {};
    }

    std::string out{};
    out.reserve(
        std::accumulate(lines.begin(), lines.end(), std::size_t{0},
                        [](std::size_t acc, const std::string& s) {
                            return acc + s.size() + 1U; /* +1 for '\n' */
                        }));

    for (std::size_t i{0U}; i < lines.size(); ++i) {
        out += lines[i];
        if (i + 1U < lines.size()) {
            out += '\n';
        }
    }

    return out;
}

}  // namespace diamond
