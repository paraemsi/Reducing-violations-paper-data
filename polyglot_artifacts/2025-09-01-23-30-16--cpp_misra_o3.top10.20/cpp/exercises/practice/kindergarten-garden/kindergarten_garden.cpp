#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace kindergarten_garden {

namespace {
/* Helper: split the two-row diagram into row[0] and row[1]. */
[[nodiscard]] std::array<std::string, 2U> split_rows(std::string_view diagram)
{
    const std::size_t newline_pos{diagram.find('\n')};

    if (newline_pos == std::string_view::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by '\\n'");
    }

    const std::string first_row{diagram.substr(0U, newline_pos)};
    const std::string second_row{diagram.substr(newline_pos + 1U)};

    if ((first_row.length() != second_row.length()) || ((first_row.length() % 2U) != 0U)) {
        throw std::invalid_argument("both rows must have the same even length");
    }

    return {first_row, second_row};
}
}  // namespace

/* ---------------- garden : public interface ---------------- */

garden::garden(std::string_view diagram)
    : pupils_{default_pupils_.begin(), default_pupils_.end()},
      rows_{split_rows(diagram)}
{
}

garden::garden(std::string_view diagram,
               const std::vector<std::string>& students)
    : pupils_{students},
      rows_{split_rows(diagram)}
{
    std::sort(pupils_.begin(), pupils_.end());
}

std::array<Plants, 4U> garden::plants(std::string_view pupil) const
{
    const auto it{std::find(pupils_.cbegin(), pupils_.cend(), pupil)};
    if (it == pupils_.cend()) {
        throw std::out_of_range("unknown pupil");
    }

    const std::uint32_t index{static_cast<std::uint32_t>(std::distance(pupils_.cbegin(), it))};
    const std::uint32_t col  {(index * 2U)};

    if ((static_cast<std::size_t>(col + 1U)) >= rows_[0U].length()) {
        throw std::logic_error("diagram is too short for the pupil list");
    }

    const std::array<Plants, 4U> result{
        char_to_plant(rows_[0U][col]),
        char_to_plant(rows_[0U][col + 1U]),
        char_to_plant(rows_[1U][col]),
        char_to_plant(rows_[1U][col + 1U])
    };

    return result;
}

/* ---------------- garden : private helpers ---------------- */

Plants garden::char_to_plant(char code)
{
    /* Equality on characters is allowed by the rules. */
    if (code == 'G') { return Plants::grass; }
    if (code == 'C') { return Plants::clover; }
    if (code == 'R') { return Plants::radishes; }
    if (code == 'V') { return Plants::violets; }

    throw std::invalid_argument("invalid plant code");
}

/* ---------------- free helper function ---------------- */

std::array<Plants, 4U> plants(std::string_view diagram, std::string_view pupil)
{
    const garden g{diagram};
    return g.plants(pupil);
}

}  // namespace kindergarten_garden
