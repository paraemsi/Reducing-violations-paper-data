#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>  // for std::move
#include <array>

namespace kindergarten_garden {

const std::vector<std::string> garden::default_students_{
    "Alice",  "Bob",    "Charlie", "David",
    "Eve",    "Fred",   "Ginny",   "Harriet",
    "Ileana", "Joseph", "Kincaid", "Larry"};


Plants garden::to_plant(char c) {
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

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Split the diagram into its two rows.
    auto pos = diagram.find('\n');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain exactly two rows separated by a newline");
    }
    std::string row1 = diagram.substr(0, pos);
    std::string row2 = diagram.substr(pos + 1);

    // Validate row lengths.
    if (row1.size() != row2.size() || row1.size() % 2 != 0) {
        throw std::invalid_argument("Rows must be of equal even length");
    }

    // Prepare the roster, sorted alphabetically (truncate default list if needed).
    std::size_t expected_students = row1.size() / 2;

    std::vector<std::string> roster;
    if (students.empty()) {
        if (expected_students > default_students_.size()) {
            throw std::invalid_argument("Too many cups for the default roster");
        }
        roster.assign(default_students_.begin(),
                      default_students_.begin() + expected_students);
    } else {
        roster = students;
        if (roster.size() != expected_students) {
            throw std::invalid_argument("Number of students does not match number of cup pairs");
        }
        std::sort(roster.begin(), roster.end());
    }

    // Assign the plants to each student.
    for (std::size_t i = 0; i < roster.size(); ++i) {
        std::vector<Plants> list;
        list.reserve(4);
        list.push_back(to_plant(row1[2 * i]));
        list.push_back(to_plant(row1[2 * i + 1]));
        list.push_back(to_plant(row2[2 * i]));
        list.push_back(to_plant(row2[2 * i + 1]));
        assignment_.emplace(roster[i], std::move(list));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    auto it = assignment_.find(student);
    if (it == assignment_.end()) {
        throw std::out_of_range("Student not found");
    }
    return it->second;
}

// Free-function wrapper used by the unit tests.
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students) {
    garden g(diagram, students);
    auto vec = g.plants(student);
    return {vec[0], vec[1], vec[2], vec[3]};
}

}  // namespace kindergarten_garden
