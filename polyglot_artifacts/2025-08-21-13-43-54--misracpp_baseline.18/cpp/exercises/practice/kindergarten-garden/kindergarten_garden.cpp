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
        case 'V': return Plants::violets;
        case 'R': return Plants::radishes;
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

kindergarten_garden::kindergarten_garden(const std::string& diagram) {
    // Remove any leading newline
    std::string diag = diagram;
    if (!diag.empty() && diag[0] == '\n') {
        diag = diag.substr(1);
    }
    size_t pos = diag.find('\n');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Diagram must have two rows");
    }
    std::string row1 = diag.substr(0, pos);
    std::string row2 = diag.substr(pos + 1);

    // Assign plants to students alphabetically
    std::vector<std::string> sorted_students = students_;
    std::sort(sorted_students.begin(), sorted_students.end());

    for (size_t i = 0; i < sorted_students.size(); ++i) {
        std::vector<Plants> plants;
        size_t idx = i * 2;
        if (idx + 1 < row1.size() && idx + 1 < row2.size()) {
            plants.push_back(char_to_plant(row1[idx]));
            plants.push_back(char_to_plant(row1[idx + 1]));
            plants.push_back(char_to_plant(row2[idx]));
            plants.push_back(char_to_plant(row2[idx + 1]));
        }
        student_plants_[sorted_students[i]] = plants;
    }
}

std::vector<Plants> kindergarten_garden::plants(const std::string& student) const {
    auto it = student_plants_.find(student);
    if (it != student_plants_.end()) {
        return it->second;
    }
    return {};
}

// Static function for test suite compatibility
std::vector<Plants> kindergarten_garden::plants(const std::string& diagram, const std::string& student) {
    kindergarten_garden garden(diagram);
    return garden.plants(student);
}

}  // namespace kindergarten_garden
