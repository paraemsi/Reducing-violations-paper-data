#include "kindergarten_garden.h"

#include <stdexcept>
#include <algorithm>
#include <utility>

namespace kindergarten_garden {
namespace {

// Convert diagram character to plant enum.
inline Plants char_to_plant(char c) {
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
            throw std::invalid_argument{"invalid plant code"};
    }
}

}  // namespace

garden::garden(std::string_view diagram, std::vector<std::string> students) {
    // Remove an optional leading newline for robustness.
    if (!diagram.empty() && diagram.front() == '\n') {
        diagram.remove_prefix(1);
    }

    const auto newline_pos = diagram.find('\n');
    if (newline_pos == std::string_view::npos) {
        throw std::invalid_argument{"diagram must contain two rows"};
    }

    const std::string_view row1 = diagram.substr(0, newline_pos);
    const std::string_view row2 = diagram.substr(newline_pos + 1);

    if (row1.size() != row2.size() || row1.empty()) {
        throw std::invalid_argument{"rows must be the same non-zero length"};
    }

    // Ensure there are exactly 2 cups per student per row.
    if (row1.size() % 2 != 0) {
        throw std::invalid_argument{"row length must be even"};
    }

    // Sort roster alphabetically as required by the rules.
    std::sort(students.begin(), students.end());

    const std::size_t expected_students = row1.size() / 2;
    if (students.size() != expected_students) {
        throw std::invalid_argument{"roster size does not match diagram"};
    }

    assignments_.reserve(expected_students);

    for (std::size_t i = 0; i < expected_students; ++i) {
        std::array<Plants, 4> p{
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1])};

        assignments_.emplace(students[i], p);
    }
}

std::array<Plants, 4> garden::plants(const std::string& student) const {
    const auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::out_of_range{"student not found"};
    }
    return it->second;
}

std::array<Plants, 4> plants(std::string_view diagram,
                             const std::string& student,
                             std::vector<std::string> students) {
    garden g{diagram, std::move(students)};
    return g.plants(student);
}

}  // namespace kindergarten_garden
