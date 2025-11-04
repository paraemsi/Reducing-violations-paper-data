#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <array>

namespace kindergarten_garden {

namespace {

Plants char_to_plant(char c) {
    switch (c) {
        case 'C':
            return Plants::clover;
        case 'G':
            return Plants::grass;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument("Unknown plant code");
    }
}

}  // namespace

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students) {
    auto newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }

    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);

    // Remove any trailing carriage-return / newline characters that may be present
    while (!row2.empty() && (row2.back() == '\n' || row2.back() == '\r')) {
        row2.pop_back();
    }

    std::vector<std::string> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end());

    for (std::size_t i = 0; i < sorted_students.size(); ++i) {
        const std::size_t index = i * 2;
        if (index + 1 >= row1.size() || index + 1 >= row2.size()) {
            // Not enough cups for this student; ignore.
            break;
        }

        std::vector<Plants> plants_for_student{
            char_to_plant(row1[index]),
            char_to_plant(row1[index + 1]),
            char_to_plant(row2[index]),
            char_to_plant(row2[index + 1]),
        };

        assignments_.emplace(sorted_students[i], std::move(plants_for_student));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it != assignments_.end()) {
        return it->second;
    }
    return {};
}

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students) {
    garden g(diagram, students);
    auto vec = g.plants(student);
    if (vec.size() != 4) {
        throw std::runtime_error("Expected exactly four plants for student");
    }
    std::array<Plants, 4> arr{};
    std::copy(vec.begin(), vec.end(), arr.begin());
    return arr;
}
}  // namespace kindergarten_garden
