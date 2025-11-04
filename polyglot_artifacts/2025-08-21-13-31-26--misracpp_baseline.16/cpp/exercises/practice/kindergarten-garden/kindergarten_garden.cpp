#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

Plant Garden::char_to_plant(char c) {
    switch (c) {
        case 'V': return Plant::violets;
        case 'R': return Plant::radishes;
        case 'C': return Plant::clover;
        case 'G': return Plant::grass;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

Garden::Garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Split diagram into two rows
    size_t pos = diagram.find('\n');
    std::string row1, row2;
    if (pos != std::string::npos) {
        row1 = diagram.substr(0, pos);
        row2 = diagram.substr(pos + 1);
    } else {
        // If no newline, assume two rows are concatenated
        row1 = diagram.substr(0, diagram.size() / 2);
        row2 = diagram.substr(diagram.size() / 2);
    }

    // Copy and sort students alphabetically
    std::vector<std::string> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end());

    for (size_t i = 0; i < sorted_students.size(); ++i) {
        std::vector<Plant> plants;
        if (2 * i + 1 < row1.size() && 2 * i + 1 < row2.size()) {
            plants.push_back(char_to_plant(row1[2 * i]));
            plants.push_back(char_to_plant(row1[2 * i + 1]));
            plants.push_back(char_to_plant(row2[2 * i]));
            plants.push_back(char_to_plant(row2[2 * i + 1]));
        }
        student_plants_[sorted_students[i]] = plants;
    }
}

std::vector<Plant> Garden::plants(const std::string& student) const {
    auto it = student_plants_.find(student);
    if (it != student_plants_.end()) {
        return it->second;
    }
    return {};
}

std::vector<Plant> plants(const std::string& diagram, const std::string& student) {
    Garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
