#include "kindergarten_garden.h"

#include <stdexcept>
#include <string>

namespace kindergarten_garden {

namespace {
/* List of students in alphabetical order as mandated by the exercise. */
constexpr std::array<std::string_view, 12U> k_students{
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};
}  // namespace

/* static */ std::uint32_t Garden::student_index(std::string_view name)
{
    for (std::uint32_t idx{0U}; idx < static_cast<std::uint32_t>(k_students.size()); ++idx) {
        if (k_students[idx] == name) {
            return idx;
        }
    }
    throw std::out_of_range("Unknown student name");
}

/* static */ Plant Garden::to_plant(char cup)
{
    /* Only equality on character literals is permitted by the MISRA rule set. */
    if (cup == 'G') {
        return Plant::grass;
    }
    if (cup == 'C') {
        return Plant::clover;
    }
    if (cup == 'R') {
        return Plant::radishes;
    }
    if (cup == 'V') {
        return Plant::violets;
    }

    throw std::invalid_argument("Invalid cup code");
}

Garden::Garden(std::string_view diagram)
{
    /* The diagram should have exactly two rows separated by '\n'. */
    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string_view::npos) {
        throw std::invalid_argument("Diagram must contain two rows");
    }

    const std::string_view first_row{diagram.substr(0U, newline_pos)};
    const std::string_view second_row{diagram.substr((newline_pos + 1U))};

    /* Verify expected length: 2 cups per student per row. */
    const std::size_t expected_len{k_students.size() * 2U};
    if ((first_row.length() != expected_len) || (second_row.length() != expected_len)) {
        throw std::invalid_argument("Row length does not match student count");
    }

    for (std::uint32_t idx{0U}; idx < static_cast<std::uint32_t>(k_students.size()); ++idx) {
        const std::uint32_t offset{static_cast<std::uint32_t>(idx * 2U)};

        m_student_plants[idx][0U] = to_plant(first_row[offset]);
        m_student_plants[idx][1U] = to_plant(first_row[offset + 1U]);
        m_student_plants[idx][2U] = to_plant(second_row[offset]);
        m_student_plants[idx][3U] = to_plant(second_row[offset + 1U]);
    }
}

std::array<Plant, 4U> Garden::plants(std::string_view student) const
{
    const std::uint32_t idx{student_index(student)};

    /* Return the fixed-size array of plants directly. */
    return m_student_plants[idx];
}

/* -------------------------------------------------------------------------- */
/* Free helper function required by the tests.                                */
/* -------------------------------------------------------------------------- */
std::array<Plant, 4U> plants(std::string_view diagram, std::string_view student)
{
    const Garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
