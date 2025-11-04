#include "kindergarten_garden.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

garden::garden(const std::string& diagram)
    : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students) {
    // Copy and sort student names to ensure alphabetical assignment
    std::vector<std::string> kids = students;
    std::sort(kids.begin(), kids.end());

    // Split the diagram into its two rows
    std::istringstream stream(diagram);
    std::string row1;
    std::string row2;
    std::getline(stream, row1);
    std::getline(stream, row2);

    // Handle a possible leading blank line
    if (row1.empty() && !row2.empty()) {
        row1.swap(row2);
        std::string tmp;
        std::getline(stream, tmp);  // consume the second row
        row2 = tmp;
    }

    if (row1.size() != row2.size() ||
        row1.size() % 2 != 0 ||
        row1.size() / 2 > kids.size()) {
        throw std::invalid_argument("Invalid garden diagram");
    }

    const std::size_t num_students = row1.size() / 2;

    for (std::size_t i = 0; i < num_students; ++i) {
        std::array<Plants, 4> plist{{
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1])
        }};
        assignments_.emplace(kids[i], plist);
    }
}

std::array<Plants, 4> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::out_of_range("Student not found");
    }
    return it->second;
}

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

std::vector<std::string> garden::default_students() {
    return {"Alice",  "Bob",   "Charlie", "David",
            "Eve",    "Fred",  "Ginny",   "Harriet",
            "Ileana", "Joseph","Kincaid", "Larry"};
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
