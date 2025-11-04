#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

//--------------------------------------------------------------------------
//  Static data
//--------------------------------------------------------------------------

const std::vector<std::string> garden::default_students{
    "Alice",  "Bob",     "Charlie", "David",
    "Eve",    "Fred",    "Ginny",   "Harriet",
    "Ileana", "Joseph",  "Kincaid", "Larry"
};

//--------------------------------------------------------------------------
//  Construction
//--------------------------------------------------------------------------

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students_input) {
    // Build the roster – provided list or the default one, then sort it.
    std::vector<std::string> students =
        students_input.empty() ? default_students : students_input;
    std::sort(students.begin(), students.end());

    // Strip an optional leading newline and split into two rows.
    std::string rows = diagram;
    if (!rows.empty() && rows.front() == '\n') {
        rows.erase(rows.begin());
    }
    auto newline_pos = rows.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument{"Diagram must contain two rows separated by a newline"};
    }
    std::string row1 = rows.substr(0, newline_pos);
    std::string row2 = rows.substr(newline_pos + 1);

    // Map cups to students: two per row, four total per student.
    for (std::size_t i = 0; i < students.size(); ++i) {
        std::size_t idx = 2 * i;
        if (idx + 1 >= row1.size() || idx + 1 >= row2.size()) {
            break;  // Not enough cups for more students.
        }
        assignments[students[i]] = std::array<Plants, 4>{
            char_to_plant(row1[idx]), char_to_plant(row1[idx + 1]),
            char_to_plant(row2[idx]), char_to_plant(row2[idx + 1])};
    }
}

//--------------------------------------------------------------------------
//  Public API
//--------------------------------------------------------------------------

std::array<Plants, 4> garden::plants(const std::string& student) const {
    auto it = assignments.find(student);
    if (it == assignments.end()) {
        return std::array<Plants, 4>{};
    }
    return it->second;
}

//--------------------------------------------------------------------------
//  Internal helpers
//--------------------------------------------------------------------------

Plants garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:  throw std::invalid_argument{"Unknown plant character"};
    }
}

/*
 * Free function wrapper demanded by the unit-tests.
 */
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students)
{
    garden g(diagram, students);
    return g.plants(student);
}

}  // namespace kindergarten_garden
