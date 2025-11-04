#include "diamond.h"

#include <stdexcept>
#include <string_view>
#include <utility>          // for std::move

namespace diamond {

namespace {
/* Alphabet lookup used to avoid relying on character numeric values */
static constexpr std::string_view kAlphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

/* Return the zero-based position of a letter inside kAlphabet */
auto index_of_letter(char letter) -> std::size_t
{
    const std::size_t pos{kAlphabet.find(letter)};
    if (pos == std::string_view::npos) {
        throw std::invalid_argument("Letter must be between 'A' and 'Z'");
    }
    return pos;
}
}  // namespace

auto make_diamond(char target) -> std::vector<std::string>
{
    const std::size_t idx{index_of_letter(target)};
    /* Width and height of the diamond (square), calculated explicitly */
    const std::size_t size{(idx * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U)};

    std::vector<std::string> lines{};
    lines.reserve(size);

    for (std::size_t row{0U}; row < size; ++row) {
        /* Mirror the bottom half onto the top to simplify calculations */
        const std::size_t mirror_row{(row <= idx) ? row : (size - row - static_cast<std::size_t>(1U))};

        const std::size_t lead_spaces{idx - mirror_row};
        const char current_letter{kAlphabet[mirror_row]};

        std::string line{};
        line.append(lead_spaces, ' ');
        line.push_back(current_letter);

        if (mirror_row != static_cast<std::size_t>(0U)) {
            const std::size_t inner_spaces{(mirror_row * static_cast<std::size_t>(2U)) - static_cast<std::size_t>(1U)};
            line.append(inner_spaces, ' ');
            line.push_back(current_letter);
        }

        /* Trailing spaces must equal leading spaces */
        line.append(lead_spaces, ' ');

        lines.emplace_back(std::move(line));
    }

    return lines;
}

auto rows(char target) -> std::vector<std::string>
{
    /* Forward to main implementation to satisfy test expectations */
    return make_diamond(target);
}

}  // namespace diamond
