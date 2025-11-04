#include "diamond.h"

#include <vector>   // for std::vector


namespace diamond {

auto make(char target) -> std::string
{
    /* Alphabet lookup array — no numeric use of characters */
    static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr std::size_t alphabet_len{26U};

    /* Find the index of the requested letter without arithmetic on char */
    std::size_t target_index{0U};
    bool        found{false};

    for (std::size_t i{0U}; i < alphabet_len; ++i) {
        if (alphabet[i] == target) {
            target_index = i;
            found        = true;
            break;
        }
    }

    if (!found) {
        /* Invalid input: return empty string */
        return std::string{};
    }

    const std::size_t diamond_size{(target_index * 2U) + 1U};

    /* Pre-allocate: each row has diamond_size chars + '\n' (except last) */
    std::string result{};
    result.reserve((diamond_size + 1U) * diamond_size);

    for (std::size_t row{0U}; row < diamond_size; ++row) {
        const std::size_t top_half_index{(row <= target_index) ? row : (diamond_size - row - 1U)};
        const std::size_t leading_spaces{target_index - top_half_index};
        const std::size_t inner_spaces{(top_half_index == 0U) ? 0U : ((top_half_index * 2U) - 1U)};

        /* Left padding */
        result.append(leading_spaces, ' ');

        /* First letter */
        result.push_back(alphabet[top_half_index]);

        /* Inner padding + second letter (if not the first/last row) */
        if (inner_spaces > 0U) {
            result.append(inner_spaces, ' ');
            result.push_back(alphabet[top_half_index]);
        }

        /* Right padding (mirror of leading) */
        result.append(leading_spaces, ' ');

        /* Trailing newline except for the last line */
        if (row < (diamond_size - 1U)) {
            result.push_back('\n');
        }
    }

    return result;
}

auto rows(char target) -> std::vector<std::string>
{
    const std::string diamond_str{make(target)};
    std::vector<std::string> out{};
    out.reserve(diamond_str.empty() ? 0U : static_cast<std::size_t>((diamond_str.size() / 2U) + 1U));

    std::size_t start{0U};
    while (start < diamond_str.size()) {
        const std::size_t nl_pos{diamond_str.find('\n', start)};
        if (nl_pos == std::string::npos) {
            out.emplace_back(diamond_str.substr(start));
            break;
        } else {
            out.emplace_back(diamond_str.substr(start, nl_pos - start));
            start = nl_pos + 1U;
        }
    }
    return out;
}

}  // namespace diamond
