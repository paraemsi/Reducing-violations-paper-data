#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <array>
#include <ostream>

namespace kindergarten_garden {

const std::vector<std::string> garden::default_students_ = {
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};

Plants garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:  throw std::invalid_argument("Unknown plant code");
    }
}

garden::garden(const std::string& diagram)
    : garden(diagram, default_students_) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Copy and sort student names alphabetically.
    std::vector<std::string> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end());

    // Remove an optional leading newline and split the diagram into two rows.
    std::string cleaned = diagram;
    if (!cleaned.empty() && cleaned.front() == '\n') {
        cleaned.erase(0, 1);
    }
    auto newline_pos = cleaned.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }
    std::string row1 = cleaned.substr(0, newline_pos);
    std::string row2 = cleaned.substr(newline_pos + 1);

    // Trim any trailing carriage return or newline characters that may remain.
    while (!row1.empty() && (row1.back() == '\n' || row1.back() == '\r')) {
        row1.pop_back();
    }
    while (!row2.empty() && (row2.back() == '\n' || row2.back() == '\r')) {
        row2.pop_back();
    }

    if (row1.size() != row2.size()) {
        throw std::invalid_argument("Diagram rows must be of equal length");
    }

    std::size_t expected_length = sorted_students.size() * 2;
    if (row1.size() < expected_length) {
        throw std::invalid_argument("Diagram does not contain enough cups for all students");
    }

    // Assign plants: two cups per row for each student.
    for (std::size_t i = 0; i < sorted_students.size(); ++i) {
        std::size_t idx = i * 2;
        std::array<Plants, 4> p{
            char_to_plant(row1[idx]),
            char_to_plant(row1[idx + 1]),
            char_to_plant(row2[idx]),
            char_to_plant(row2[idx + 1])
        };
        assignments_.emplace(sorted_students[i], std::move(p));
    }
}

std::array<Plants, 4> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::out_of_range("Unknown student");
    }
    return it->second;
}

/* Namespace-level convenience wrapper expected by the tests */
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g{diagram};
    return g.plants(student);
}

/* Stream insertion operator for Plants enum – improves Catch output */
std::ostream& operator<<(std::ostream& os, Plants p) {
    switch (p) {
        case Plants::grass:    os << "grass";    break;
        case Plants::clover:   os << "clover";   break;
        case Plants::radishes: os << "radishes"; break;
        case Plants::violets:  os << "violets";  break;
    }
    return os;
}

}  // namespace kindergarten_garden
