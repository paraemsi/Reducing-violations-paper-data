#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> kindergarten_garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Plant kindergarten_garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plant::grass;
        case 'C': return Plant::clover;
        case 'R': return Plant::radishes;
        case 'V': return Plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

kindergarten_garden::kindergarten_garden(const std::string& diagram) {
    // Split diagram into two rows
    size_t pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, pos);
    std::string row2 = diagram.substr(pos + 1);

    for (size_t i = 0; i < students_.size(); ++i) {
        std::vector<Plant> plants;
        plants.push_back(char_to_plant(row1[2 * i]));
        plants.push_back(char_to_plant(row1[2 * i + 1]));
        plants.push_back(char_to_plant(row2[2 * i]));
        plants.push_back(char_to_plant(row2[2 * i + 1]));
        student_plants_[students_[i]] = plants;
    }
}

std::vector<Plant> kindergarten_garden::plants(const std::string& student) const {
    auto it = student_plants_.find(student);
    if (it != student_plants_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace kindergarten_garden

// Free function for test compatibility
std::vector<kindergarten_garden::Plants> kindergarten_garden::plants(const std::string& diagram, const std::string& student) {
    kindergarten_garden g(diagram);
    return g.plants(student);
}
