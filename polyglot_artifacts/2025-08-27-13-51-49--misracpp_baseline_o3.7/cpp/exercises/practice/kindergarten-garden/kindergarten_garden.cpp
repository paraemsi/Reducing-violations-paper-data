#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

namespace {

// Translate single-letter code to plant enum.
Plants char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Invalid plant code");
    }
}

}  // namespace

// Default class roster (already alphabetically ordered).
const std::vector<std::string> garden::default_students = {
    "Alice", "Bob",   "Charlie", "David",
    "Eve",   "Fred",  "Ginny",   "Harriet",
    "Ileana","Joseph","Kincaid", "Larry"
};

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students) {
    // Determine roster to use and ensure it is alphabetically ordered.
    std::vector<std::string> roster = students.empty() ? default_students : students;
    std::sort(roster.begin(), roster.end());

    // Split diagram into two rows.
    auto nl_pos = diagram.find('\n');
    if (nl_pos == std::string::npos)
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");

    std::string row1 = diagram.substr(0, nl_pos);
    std::string row2 = diagram.substr(nl_pos + 1);

    if (row1.size() != row2.size())
        throw std::invalid_argument("Both diagram rows must be the same length");

    // Build assignment map.
    for (size_t i = 0; i < roster.size(); ++i) {
        size_t col = i * 2;
        if (col + 1 >= row1.size())
            throw std::out_of_range("Diagram does not contain enough cups for all students");

        assignments.emplace(
            roster[i],
            std::vector<Plants>{
                char_to_plant(row1[col]),
                char_to_plant(row1[col + 1]),
                char_to_plant(row2[col]),
                char_to_plant(row2[col + 1])
            }
        );
    }
}

std::vector<Plants> garden::plants_for(const std::string& student) const {
    auto it = assignments.find(student);
    if (it == assignments.end())
        return {};
    return it->second;
}

// Free helper function used by the unit tests
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students)
{
    garden g(diagram, students);
    auto vec = g.plants_for(student);
    if (vec.size() != 4)
        throw std::logic_error("Each student must have exactly four plants");
    return {vec[0], vec[1], vec[2], vec[3]};
}

}  // namespace kindergarten_garden
