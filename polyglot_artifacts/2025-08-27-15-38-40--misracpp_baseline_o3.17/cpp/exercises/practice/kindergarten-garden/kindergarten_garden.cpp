#include "kindergarten_garden.h"
#include <stdexcept>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Split diagram into two rows
    std::string row1, row2;
    std::size_t newline_pos = diagram.find('\n');
    if (newline_pos != std::string::npos) {
        row1 = diagram.substr(0, newline_pos);
        row2 = diagram.substr(newline_pos + 1);
    } else {
        // If diagram has no newline, assume first half belongs to first row
        row1 = diagram.substr(0, diagram.size() / 2);
        row2 = diagram.substr(row1.size());
    }

    // Validate diagram length
    std::size_t expected_length = students.size() * 2;
    if (row1.size() != expected_length || row2.size() != expected_length) {
        throw std::invalid_argument("Diagram length does not match number of students.");
    }

    // Order students alphabetically, as cups are assigned in that order
    std::vector<std::string> ordered_students = students;
    std::sort(ordered_students.begin(), ordered_students.end());

    // Build mapping
    for (std::size_t idx = 0; idx < ordered_students.size(); ++idx) {
        std::vector<Plant> vec;
        vec.reserve(4);
        vec.push_back(char_to_plant(row1[2 * idx]));
        vec.push_back(char_to_plant(row1[2 * idx + 1]));
        vec.push_back(char_to_plant(row2[2 * idx]));
        vec.push_back(char_to_plant(row2[2 * idx + 1]));
        m_plants.emplace(ordered_students[idx], std::move(vec));
    }
}

std::vector<Plant> garden::plants(const std::string& student) const {
    auto it = m_plants.find(student);
    if (it == m_plants.end()) {
        return {};
    }
    return it->second;
}

Plant garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plant::grass;
        case 'C': return Plant::clover;
        case 'R': return Plant::radishes;
        case 'V': return Plant::violets;
        default:  throw std::invalid_argument("Invalid plant code");
    }
}

// Free helper function implementation
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g{diagram};
    auto vec = g.plants(student);
    if (vec.size() != 4) {
        throw std::invalid_argument("Each student must have exactly 4 plants.");
    }
    std::array<Plants, 4> arr{};
    std::copy(vec.begin(), vec.end(), arr.begin());
    return arr;
}

}  // namespace kindergarten_garden
