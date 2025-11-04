#include "diamond.h"

#include <string>
#include <string_view>
#include <vector>
#include <locale>

namespace diamond {

auto make_diamond(char letter) -> std::vector<std::string>
{
    constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const std::string_view alphabet_view{alphabet};

    const char              normalized_letter{
        std::toupper(letter, std::locale{})
    };

    const std::size_t       letter_index{alphabet_view.find(normalized_letter)};

    if (letter_index == std::string_view::npos) {
        return {};  // Invalid input character – return an empty result.
    }

    const std::size_t width{
        (static_cast<std::size_t>(2) * letter_index) + static_cast<std::size_t>(1)};
    const std::size_t center{letter_index};

    std::vector<std::string> top_half{};
    top_half.reserve(letter_index + static_cast<std::size_t>(1));

    for (std::size_t i{0U}; i <= letter_index; ++i) {
        std::string   line(width, ' ');
        const char    ch{alphabet_view[i]};
        const std::size_t left {center - i};
        const std::size_t right{center + i};

        line[left] = ch;
        if (right != left) {
            line[right] = ch;
        }

        top_half.push_back(line);
    }

    std::vector<std::string> result{top_half};
    for (std::size_t i{letter_index}; i > static_cast<std::size_t>(0); --i) {
        result.push_back(top_half[i - static_cast<std::size_t>(1)]);
    }

    return result;
}

auto rows(char letter) -> std::vector<std::string>
{
    return make_diamond(letter);
}

}  // namespace diamond
