#include "kindergarten_garden.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

// Definition of the default student roster (C++14 friendly, non-inline)
const std::vector<std::string> default_students{
    "Alice",  "Bob",    "Charlie", "David",
    "Eve",    "Fred",   "Ginny",   "Harriet",
    "Ileana", "Joseph", "Kincaid", "Larry"};

// Helper: translate character to plant enum
Plants garden::char_to_plant(char c) {
    switch (std::toupper(static_cast<unsigned char>(c))) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument{"Invalid plant code"};
    }
}

garden::garden(const std::string& diagram,
               std::vector<std::string> students) {
    // Ensure students are sorted alphabetically as per the rules
    std::sort(students.begin(), students.end());

    // Split diagram into two rows; ignore an optional leading newline.
    std::istringstream is(diagram);
    std::string row1, row2;
    std::getline(is, row1);
    if (row1.empty()) {               // leading '\n'
        std::getline(is, row1);
    }
    std::getline(is, row2);

    // Basic validation: two rows present and even length
    if (row1.empty() || row2.empty() || row1.size() != row2.size() ||
        row1.size() % 2 != 0) {
        throw std::invalid_argument{"Invalid garden diagram"};
    }

    std::size_t child_count = row1.size() / 2;
    if (students.size() != child_count) {
        throw std::invalid_argument{"Mismatch between diagram and students"};
    }

    for (std::size_t i = 0; i < child_count; ++i) {
        std::array<Plants, 4> p{{
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1])}};

        assignments_.emplace(students[i], std::move(p));
    }
}

std::array<Plants, 4> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::out_of_range{"Student not found"};
    }
    return it->second;
}

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g{diagram};
    return g.plants(student);
}

}  // namespace kindergarten_garden
