#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <stdexcept>

namespace kindergarten_garden {

namespace {
/* Helper : locate student index within list */
std::size_t student_index(std::vector<std::string> const& students,
                          std::string_view                 name)
{
    auto const it =
        std::find(students.cbegin(), students.cend(), std::string(name));
    if (it == students.cend()) {
        /* Student not present – caller decides how to react */
        return students.size(); /* out-of-range sentinel */
    }
    /* Safe because distance returns ptrdiff_t that fits size_t for small N */
    return static_cast<std::size_t>(std::distance(students.cbegin(), it));
}
} // namespace

/* --- garden ------------------------------------------------------------ */
garden::garden(std::string_view            diagram,
               std::vector<std::string> const& students)
    : m_students{students.empty() ? default_students() : students}
{
    /* Strip a possible leading '\n' to simplify row split */
    if ((!diagram.empty()) && (diagram.front() == '\n')) {
        diagram.remove_prefix(1U);
    }

    /* Diagram must contain exactly two rows separated by '\n' */
    auto const newline_pos = diagram.find('\n');
    if ((newline_pos == std::string_view::npos) ||
        (diagram.find('\n', newline_pos + 1U) != std::string_view::npos)) {
        throw std::invalid_argument("diagram must contain two rows");
    }

    m_rows[0U] = std::string(diagram.substr(0U, newline_pos));
    m_rows[1U] = std::string(diagram.substr(newline_pos + 1U));

    if ((m_rows[0U].size() != m_rows[1U].size()) ||
        ((m_rows[0U].size() % 2U) != 0U)) {
        throw std::invalid_argument("rows must be equal length and even");
    }
}

std::vector<plant> garden::plants(std::string_view student) const
{
    auto const idx = student_index(m_students, student);
    if (idx >= m_students.size()) {
        return {}; /* Unknown student: return empty list */
    }

    std::size_t const first_cup = idx * 2U;
    std::vector<plant> result;
    result.reserve(4U);

    result.emplace_back(to_plant(m_rows[0U][first_cup]));
    result.emplace_back(to_plant(m_rows[0U][first_cup + 1U]));
    result.emplace_back(to_plant(m_rows[1U][first_cup]));
    result.emplace_back(to_plant(m_rows[1U][first_cup + 1U]));

    return result;
}

/* --- helpers ----------------------------------------------------------- */
plant garden::to_plant(char cup)
{
    if (cup == 'V') {
        return plant::violets;
    } else if (cup == 'R') {
        return plant::radishes;
    } else if (cup == 'C') {
        return plant::clover;
    } else if (cup == 'G') {
        return plant::grass;
    } else {
        throw std::invalid_argument("invalid plant code");
    }
}

std::vector<std::string> garden::default_students()
{
    return {
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };
}

/* ------------------------------------------------------------------ */
/* Free helper function expected by the Exercism test suite           */
std::array<Plants, 4U> plants(std::string_view diagram,
                              std::string_view student)
{
    garden const g(diagram);
    auto const    vec = g.plants(student);

    if (vec.size() != 4U) {
        throw std::runtime_error("a student must have exactly four plants");
    }

    std::array<Plants, 4U> result{};
    for (std::uint32_t i = 0U; (i < 4U); ++i) {
        result[i] = vec[i];
    }
    return result;
}

}  // namespace kindergarten_garden
