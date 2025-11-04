#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

static Plants char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:
            throw std::invalid_argument("Unknown plant character");
    }
}

garden::garden(std::string_view diagram, std::vector<std::string> students)
{
    // Remove any leading newline.
    if (!diagram.empty() && diagram.front() == '\n') {
        diagram.remove_prefix(1);
    }

    // Split into two rows at the first newline.
    std::size_t pos = diagram.find('\n');
    if (pos == std::string_view::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by newline");
    }
    std::string_view row1 = diagram.substr(0, pos);
    std::string_view row2 = diagram.substr(pos + 1);

    // Trim any trailing newline or carriage-return characters that might be
    // present at the end of the rows so they don’t interfere with sizing logic.
    if (!row2.empty() && (row2.back() == '\n' || row2.back() == '\r')) {
        row2.remove_suffix(1);
    }
    if (!row1.empty() && row1.back() == '\r') {
        row1.remove_suffix(1);
    }

    if (row1.size() != row2.size()) {
        throw std::invalid_argument("Rows must be equal length");
    }
    if (row1.size() % 2 != 0) {
        throw std::invalid_argument("Each student must have two cups per row");
    }

    // Sort students alphabetically; cup assignment depends on this order.
    std::sort(students.begin(), students.end());

    std::size_t expected_cups = students.size() * 2;
    if (row1.size() != expected_cups) {
        throw std::invalid_argument("Number of cups does not match number of students");
    }

    for (std::size_t i = 0; i < students.size(); ++i) {
        std::vector<Plants> v;
        v.reserve(4);
        v.push_back(char_to_plant(row1[2 * i]));
        v.push_back(char_to_plant(row1[2 * i + 1]));
        v.push_back(char_to_plant(row2[2 * i]));
        v.push_back(char_to_plant(row2[2 * i + 1]));
        assignments_.emplace(students[i], std::move(v));
    }
}

const std::vector<Plants>& garden::plants(std::string_view student) const
{
    auto it = assignments_.find(std::string(student));
    if (it == assignments_.end()) {
        throw std::out_of_range("Student not found");
    }
    return it->second;
}

// Helper free function expected by the tests
std::array<Plants, 4> plants(std::string_view diagram, std::string_view student)
{
    garden g(diagram);
    const auto& v = g.plants(student);
    return {v[0], v[1], v[2], v[3]};
}

}  // namespace kindergarten_garden
