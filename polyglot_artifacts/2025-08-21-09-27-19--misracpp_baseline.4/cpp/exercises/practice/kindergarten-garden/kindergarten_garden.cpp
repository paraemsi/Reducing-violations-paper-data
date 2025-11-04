#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

std::vector<std::string> kindergarten_garden::default_students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Plants kindergarten_garden::char_to_plant(char c) {
    switch (c) {
        case 'V': return Plants::violets;
        case 'R': return Plants::radishes;
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

kindergarten_garden::kindergarten_garden(const std::string& diagram)
    : students_(default_students_)
{
    parse_diagram(diagram);
}

void kindergarten_garden::parse_diagram(const std::string& diagram) {
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

    // Remove any carriage returns
    row1.erase(std::remove(row1.begin(), row1.end(), '\r'), row1.end());
    row2.erase(std::remove(row2.begin(), row2.end(), '\r'), row2.end());

    for (size_t i = 0; i < students_.size(); ++i) {
        std::vector<Plants> plants_vec;
        if (2 * i + 1 < row1.size() && 2 * i + 1 < row2.size()) {
            plants_vec.push_back(char_to_plant(row1[2 * i]));
            plants_vec.push_back(char_to_plant(row1[2 * i + 1]));
            plants_vec.push_back(char_to_plant(row2[2 * i]));
            plants_vec.push_back(char_to_plant(row2[2 * i + 1]));
        }
        student_plants_[students_[i]] = plants_vec;
    }
}

std::vector<Plants> kindergarten_garden::plants(const std::string& student) const {
    auto it = student_plants_.find(student);
    if (it != student_plants_.end()) {
        return it->second;
    }
    return {};
}

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    kindergarten_garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
