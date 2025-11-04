#include "kindergarten_garden.h"

#include <algorithm>
#include <utility>
#include <stdexcept>
#include <array>
#include <cstddef>

namespace kindergarten_garden {

namespace {

/* Split the two-row diagram into its individual rows. */
std::pair<std::string, std::string> split_rows(const std::string& diagram)
{
    auto const newline_pos {diagram.find('\n')};
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline.");
    }

    std::string const first {diagram.substr(0U, newline_pos)};
    std::string const second {diagram.substr(newline_pos + 1U)};

    if (first.size() != second.size()) {
        throw std::invalid_argument("Both rows in the diagram must have equal length.");
    }

    return std::make_pair(first, second);
}

}  // unnamed namespace

/* ---------- garden implementation --------------------------------------- */

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
{
    /* Prepare the student roster in alphabetical order. */
    std::vector<std::string> roster {students};
    std::sort(roster.begin(), roster.end());

    /* Split the diagram into two rows. */
    auto const [row1, row2] {split_rows(diagram)};

    /* Verify that the diagram length matches the roster size. */
    if ((row1.size() / 2U) != roster.size()) {
        throw std::invalid_argument("Diagram does not match the number of students.");
    }

    /* Assign plants to each student. */
    for (std::size_t i {0U}; i < roster.size(); ++i) {
        std::size_t const index {(i * 2U)};
        std::vector<Plants> allocation;
        allocation.reserve(4U);

        allocation.push_back(char_to_plant(row1[index]));
        allocation.push_back(char_to_plant(row1[(index + 1U)]));
        allocation.push_back(char_to_plant(row2[index]));
        allocation.push_back(char_to_plant(row2[(index + 1U)]));

        m_assignments.emplace(roster[i], allocation);
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    auto const it {m_assignments.find(student)};
    if (it == m_assignments.end()) {
        throw std::out_of_range("Student not found.");
    }

    return it->second;
}

const std::vector<std::string>& garden::default_student_list()
{
    static const std::vector<std::string> default_roster {
        "Alice",  "Bob",     "Charlie", "David",
        "Eve",    "Fred",    "Ginny",   "Harriet",
        "Ileana", "Joseph",  "Kincaid", "Larry"
    };
    return default_roster;
}

Plants garden::char_to_plant(char code)
{
    if (code == 'G') {
        return Plants::grass;
    } else if (code == 'C') {
        return Plants::clover;
    } else if (code == 'R') {
        return Plants::radishes;
    } else if (code == 'V') {
        return Plants::violets;
    } else {
        throw std::invalid_argument("Invalid plant code in diagram.");
    }
}

}  // namespace kindergarten_garden
