#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

namespace {
Plants char_to_plant(char c) {
    switch (c) {
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}
}  // namespace

std::vector<std::string> default_students() {
    return {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}

garden::garden(const std::string& diagram, std::vector<std::string> students) {
    // Split diagram into two rows
    const auto newline_pos = diagram.find('\n');
    const std::string row1 = diagram.substr(0, newline_pos);
    const std::string row2 = (newline_pos == std::string::npos) ? std::string{} : diagram.substr(newline_pos + 1);

    // Assign cups to students in alphabetical order
    std::sort(students.begin(), students.end());

    const std::size_t cups_per_row = std::min(row1.size(), row2.size());
    const std::size_t num_students = cups_per_row / 2;

    for (std::size_t i = 0; i < num_students; ++i) {
        std::vector<Plants> ps;
        ps.reserve(4);
        ps.push_back(char_to_plant(row1[2 * i]));
        ps.push_back(char_to_plant(row1[2 * i + 1]));
        ps.push_back(char_to_plant(row2[2 * i]));
        ps.push_back(char_to_plant(row2[2 * i + 1]));
        roster_.emplace(students[i], std::move(ps));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    const auto it = roster_.find(student);
    if (it == roster_.end()) {
        return {};
    }
    return it->second;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram, default_students());
    const auto v = g.plants(student);
    if (v.size() == 4) {
        return {v[0], v[1], v[2], v[3]};
    }
    return {};
}

}  // namespace kindergarten_garden
