#include "kindergarten_garden.h"

#include <array>
#include <string_view>
#include <algorithm>

namespace kindergarten_garden {

namespace {
/* Default list of students in alphabetical order */
static constexpr std::array<std::string_view, 12U> default_students{
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"};

/* Helper to convert a diagram character to a Plants value */
inline Plants char_to_plant(char c) noexcept
{
    switch (c) {
        case 'C':
            return Plants::clover;
        case 'G':
            return Plants::grass;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            /* Unknown character – treat as grass. */
            return Plants::grass;
    }
}
}  // namespace

std::array<Plants, 4U> plants(std::string_view diagram, std::string_view student)
{
    const auto it = std::find(default_students.begin(), default_students.end(), student);
    if (it == default_students.end()) {
        return {};  /* Unknown student – return empty result. */
    }

    const std::size_t index = static_cast<std::size_t>(std::distance(default_students.begin(), it));

    /* Split the diagram into its two rows. */
    const std::size_t newline_pos = diagram.find('\n');
    std::string_view first_row{};
    std::string_view second_row{};

    if (newline_pos != std::string_view::npos) {
        first_row  = diagram.substr(0U, newline_pos);
        second_row = diagram.substr(newline_pos + 1U);
    } else {
        first_row  = diagram;
        second_row = {};
    }

    const std::size_t left  = (index * 2U);
    const std::size_t right = left + 1U;

    std::array<Plants, 4U> result{Plants::grass, Plants::grass,
                                  Plants::grass, Plants::grass};

    if ((right < first_row.length()) && (right < second_row.length())) {
        result[0] = char_to_plant(first_row[left]);
        result[1] = char_to_plant(first_row[right]);
        result[2] = char_to_plant(second_row[left]);
        result[3] = char_to_plant(second_row[right]);
    } else if (right < first_row.length()) {
        /* Second row missing – only populate from first row. */
        result[0] = char_to_plant(first_row[left]);
        result[1] = char_to_plant(first_row[right]);
    }

    return result;
}

}  // namespace kindergarten_garden
