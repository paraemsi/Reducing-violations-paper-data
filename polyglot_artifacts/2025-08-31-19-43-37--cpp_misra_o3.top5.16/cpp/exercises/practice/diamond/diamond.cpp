#include "diamond.h"

#include <cstddef>   // for std::size_t
#include <string>
#include <vector>

namespace diamond {

auto rows(char letter) -> std::vector<std::string>
{
    using char_int = std::char_traits<char>::int_type;
    const char_int letter_code = std::char_traits<char>::to_int_type(letter);
    constexpr char_int a_code   = std::char_traits<char>::to_int_type('A');
    constexpr char_int z_code   = std::char_traits<char>::to_int_type('Z');

    if ((letter_code < a_code) || (letter_code > z_code)) {
        return std::vector<std::string>(); /* invalid input */
    }

    constexpr const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::size_t max_index = std::string(alphabet).find(letter);

    const std::size_t diamond_size = (max_index * 2U) + 1U;

    std::vector<std::string> rows_vec;
    rows_vec.reserve(diamond_size);

    for (std::size_t i = 0U; i < diamond_size; ++i) {
        const std::size_t top_half_index =
            (i <= max_index) ? i : ((diamond_size - 1U) - i);

        const char current_letter = alphabet[top_half_index];

        std::string row(diamond_size, ' ');

        const std::size_t left_pos = max_index - top_half_index;
        row[left_pos] = current_letter;

        if (top_half_index != 0U) {
            const std::size_t right_pos = max_index + top_half_index;
            row[right_pos] = current_letter;
        }

        rows_vec.emplace_back(row);
    }

    return rows_vec;
}

auto make_diamond(char letter) -> std::string
{
    /* Re-use the already validated and prepared representation
     * returned by rows(), then join it with line breaks.
     */
    const auto rows_vec = rows(letter);

    if (rows_vec.empty()) {
        return std::string(); /* invalid input -> empty result */
    }

    std::string result;
    for (std::size_t idx = 0U; idx < rows_vec.size(); ++idx) {
        result += rows_vec[idx];
        if ((idx + 1U) < rows_vec.size()) {
            result += '\n';
        }
    }

    return result;
}

}  // namespace diamond
