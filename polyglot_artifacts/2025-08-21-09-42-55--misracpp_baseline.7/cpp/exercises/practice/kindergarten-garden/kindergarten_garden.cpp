#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

Plants Garden::char_to_plant(char c) {
    switch (c) {
        case 'V': return Plants::violets;
        case 'R': return Plants::radishes;
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

const std::vector<std::string> default_students_vec = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};
const std::vector<std::string>& Garden::default_students_ = default_students_vec;

Garden::Garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Split diagram into two rows
    size_t pos = diagram.find('\n');
    std::string row1, row2;
    if (pos != std::string::npos) {
        row1 = diagram.substr(0, pos);
        row2 = diagram.substr(pos + 1);
    } else {
        // If no newline, assume first half is row1, second half is row2
        row1 = diagram.substr(0, diagram.size() / 2);
        row2 = diagram.substr(diagram.size() / 2);
    }

    // Use default students if students is empty
    const std::vector<std::string>& students_to_use =
        students.empty() ? default_students_ : students;

    // Copy and sort students
    std::vector<std::string> sorted_students = students_to_use;
    std::sort(sorted_students.begin(), sorted_students.end());

    for (size_t i = 0; i < sorted_students.size(); ++i) {
        std::vector<Plants> plants;
        for (int j = 0; j < 2; ++j) {
            plants.push_back(char_to_plant(row1[2 * i + j]));
            plants.push_back(char_to_plant(row2[2 * i + j]));
        }
        student_plants_[sorted_students[i]] = plants;
    }
}

std::vector<Plants> Garden::plants(const std::string& student) const {
    auto it = student_plants_.find(student);
    if (it != student_plants_.end()) {
        return it->second;
    }
    return {};
}

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    Garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
