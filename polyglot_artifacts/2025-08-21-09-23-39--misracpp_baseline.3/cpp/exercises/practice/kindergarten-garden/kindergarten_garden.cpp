#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

namespace {
    Plants char_to_plant(char c) {
        switch (c) {
            case 'V': return Plants::violets;
            case 'R': return Plants::radishes;
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            default: throw std::invalid_argument("Unknown plant code");
        }
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
        std::vector<Plants> plants_vec;
        size_t idx = i * 2;
        if (idx + 1 < row1.size() && idx + 1 < row2.size()) {
            plants_vec.push_back(char_to_plant(row1[idx]));
            plants_vec.push_back(char_to_plant(row1[idx + 1]));
            plants_vec.push_back(char_to_plant(row2[idx]));
            plants_vec.push_back(char_to_plant(row2[idx + 1]));
        }
        student_plants_[sorted_students[i]] = plants_vec;
    }
}

std::vector<Plants> Garden::plants(const std::string& student) const {
    auto it = student_plants_.find(student);
    if (it != student_plants_.end()) {
        return it->second;
    }
    return {};
}

// Standalone function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    static const std::vector<std::string> default_students = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    Garden g(diagram, default_students);
    return g.plants(student);
}

}  // namespace kindergarten_garden
