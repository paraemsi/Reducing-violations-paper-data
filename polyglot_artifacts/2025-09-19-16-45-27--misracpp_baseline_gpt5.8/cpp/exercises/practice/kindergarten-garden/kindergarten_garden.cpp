#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace kindergarten_garden {

namespace {
const std::vector<std::string> kDefaultStudents{
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"};

inline Plants char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}
}  // namespace

garden::garden(const std::string& diagram)
    : garden(diagram, kDefaultStudents) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Split diagram into two rows
    auto newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);

    // Prepare sorted student list (assignment is alphabetical)
    std::vector<std::string> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end());

    // Validate dimensions
    if (row1.size() != row2.size()) {
        throw std::invalid_argument("Both rows must have the same number of cups");
    }
    if ((row1.size() % 2) != 0) {
        throw std::invalid_argument("Each row must contain an even number of cups");
    }
    // Determine how many students can be assigned based on available cups
    std::size_t assignable = std::min(sorted_students.size(), row1.size() / 2);

    // Assign plants: two per row, four total per student
    for (std::size_t i = 0; i < assignable; ++i) {
        std::size_t idx = i * 2;
        std::array<Plants, 4> ps{
            char_to_plant(row1.at(idx)),
            char_to_plant(row1.at(idx + 1)),
            char_to_plant(row2.at(idx)),
            char_to_plant(row2.at(idx + 1))
        };
        assignments_.emplace(sorted_students[i], ps);
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        return {};
    }
    const auto& arr = it->second;
    return std::vector<Plants>(arr.begin(), arr.end());
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    auto v = g.plants(student);
    std::array<Plants, 4> out{};
    for (std::size_t i = 0; i < out.size() && i < v.size(); ++i) {
        out[i] = v[i];
    }
    return out;
}

}  // namespace kindergarten_garden
