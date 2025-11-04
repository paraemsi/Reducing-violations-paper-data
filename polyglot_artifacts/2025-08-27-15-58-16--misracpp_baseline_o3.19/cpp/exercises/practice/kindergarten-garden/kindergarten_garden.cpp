#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

// Default, alphabetically-ordered list of students.
const std::vector<std::string> Garden::default_students_ = {
    "Alice",  "Bob",   "Charlie", "David",  "Eve",     "Fred",
    "Ginny",  "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};

// Convert a diagram character to the corresponding Plant.
Plants Garden::char_to_plant(char c) {
    switch (c) {
        case 'R':
            return Plants::radishes;
        case 'C':
            return Plants::clover;
        case 'G':
            return Plants::grass;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument{"Unknown plant character"};
    }
}

// Delegating constructor using the default student list.
Garden::Garden(std::string_view diagram)
    : Garden(diagram, default_students_) {}

// Main constructor that accepts a custom student list.
Garden::Garden(std::string_view diagram,
               const std::vector<std::string>& students_input) {
    // Copy and alphabetically sort the supplied student list.
    std::vector<std::string> students{students_input};
    std::sort(students.begin(), students.end());

    // Split the diagram into its two rows.
    std::string diag{diagram};
    auto newline_pos = diag.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument{
            "Diagram must contain two rows separated by a newline"};
    }
    std::string row1 = diag.substr(0, newline_pos);
    std::string row2 = diag.substr(newline_pos + 1);
    // Remove a possible trailing newline from the second row so that both
    // rows have identical widths.
    if (!row2.empty() && row2.back() == '\n') {
        row2.pop_back();
    }

    if (row1.size() != row2.size()) {
        throw std::invalid_argument{"Both diagram rows must have the same length"};
    }
    if (row1.size() != students.size() * 2) {
        throw std::invalid_argument{
            "Diagram width does not match twice the number of students"};
    }

    // Build the assignments map: four plants per student.
    for (std::size_t i = 0; i < students.size(); ++i) {
        std::array<Plants,4> pots{{
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1])}};
        assignments_.emplace(students[i], pots);
    }
}

// Retrieve the four plants assigned to the specified student.
std::array<Plants,4> Garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::invalid_argument{"Unknown student"};
    }
    return it->second;
}

std::array<Plants,4> plants(std::string_view diagram, const std::string& student) {
    Garden g{diagram};
    return g.plants(std::string{student});
}

}  // namespace kindergarten_garden
