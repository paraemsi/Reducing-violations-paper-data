#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <array>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

namespace {

/* Helper translating diagram letter to enum plant */
inline Plants char_to_plant(char code)
{
    switch (code) {
        case 'R':
            return Plants::radishes;
        case 'C':
            return Plants::clover;
        case 'G':
            return Plants::grass;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument("Invalid plant code");
    }
}

}  // namespace

/* Default, alphabetically-sorted list of students */
const std::vector<std::string>& garden::default_students()
{
    static const std::vector<std::string> list{
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"};
    return list;
}

/* Construct a garden from its diagram and (optionally) a student list */
garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    /* Split diagram into two rows */
    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows");
    }

    const std::string row1{diagram.substr(0U, newline_pos)};
    const std::string row2{diagram.substr(newline_pos + 1U)};

    /* Determine ordering of students (always alphabetical) */
    std::vector<std::string> ordered{students};
    std::sort(ordered.begin(), ordered.end());

    for (std::size_t idx{0U}; idx < ordered.size(); ++idx) {
        const std::size_t start{idx * 2U};              /* two cups per row   */
        const std::size_t second{(idx * 2U) + 1U};

        if (((second) >= row1.length()) || ((second) >= row2.length())) {
            throw std::out_of_range("Diagram too short for students");
        }

        std::vector<Plants> p{
            char_to_plant(row1[start]),
            char_to_plant(row1[second]),
            char_to_plant(row2[start]),
            char_to_plant(row2[second])
        };

        (void)m_assignments.emplace(ordered[idx], std::move(p));
    }
}

/* Retrieve the four plants belonging to 'student' */
std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it{m_assignments.find(student)};
    if (it == m_assignments.end()) {
        throw std::out_of_range("Unknown student");
    }
    return it->second;
}

/* Free helper constructing a temporary garden and returning student plants */
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    const garden g{diagram};
    const std::vector<Plants> vec{g.plants(student)};
    if (vec.size() != 4U) {
        throw std::out_of_range("Student must have exactly 4 plants");
    }
    std::array<Plants, 4U> arr{{vec[0U], vec[1U], vec[2U], vec[3U]}};
    return arr;
}

}  // namespace kindergarten_garden
