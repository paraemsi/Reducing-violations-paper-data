#include "kindergarten_garden.h"

#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

const std::vector<std::string> garden::default_students{
    "Alice",  "Bob",     "Charlie", "David",  "Eve",     "Fred",
    "Ginny",  "Harriet", "Ileana",  "Joseph", "Kincaid", "Larry"};

Plants garden::char_to_plant(char c) {
    switch (c) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument("Unknown plant code");
    }
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students) {
    // Determine student ordering (alphabetically)
    std::vector<std::string> roster =
        students.empty() ? default_students : students;
    if (!students.empty()) {
        std::sort(roster.begin(), roster.end());
    }

    // Extract the two rows from diagram
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    // Skip potential leading empty line
    while (std::getline(iss, row1)) {
        if (!row1.empty())
            break;
    }
    std::getline(iss, row2);

    for (std::size_t i = 0; i < roster.size(); ++i) {
        std::size_t pos = 2 * i;
        if (pos + 1 >= row1.size() || pos + 1 >= row2.size()) {
            // Not enough cups; stop processing further students
            break;
        }
        std::array<Plants, 4> cups{
            char_to_plant(row1[pos]),
            char_to_plant(row1[pos + 1]),
            char_to_plant(row2[pos]),
            char_to_plant(row2[pos + 1])};

        assignments_.emplace(roster[i], cups);
    }
}

const std::array<Plants, 4>& garden::plants(const std::string& student) const {
    return assignments_.at(student);
}

// Free-function wrapper expected by the test suite
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
