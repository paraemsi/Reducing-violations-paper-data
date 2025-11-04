#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> kindergarten_garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Plants kindergarten_garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

kindergarten_garden::kindergarten_garden(const std::string& diagram) {
    // Split diagram into two rows
    size_t pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, pos);
    std::string row2 = (pos != std::string::npos) ? diagram.substr(pos + 1) : "";

    for (size_t i = 0; i < students_.size(); ++i) {
        std::vector<Plants> plants;
        // Each student gets 2 cups per row, so 4 total
        if (row1.size() >= 2 * (i + 1)) {
            plants.push_back(char_to_plant(row1[2 * i]));
            plants.push_back(char_to_plant(row1[2 * i + 1]));
        }
        if (row2.size() >= 2 * (i + 1)) {
            plants.push_back(char_to_plant(row2[2 * i]));
            plants.push_back(char_to_plant(row2[2 * i + 1]));
        }
        student_plants_[students_[i]] = plants;
    }
}

std::vector<Plants> kindergarten_garden::plants(const std::string& student) const {
    auto it = student_plants_.find(student);
    if (it != student_plants_.end()) {
        return it->second;
    }
    return {};
}

// Static interface for test compatibility
std::vector<Plants> kindergarten_garden::plants(const std::string& diagram, const std::string& student) {
    kindergarten_garden kg(diagram);
    return kg.plants(student);
}

}  // namespace kindergarten_garden
