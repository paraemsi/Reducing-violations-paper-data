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

    // Default student list, alphabetically
    const std::vector<std::string> default_students{
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}

Garden::Garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Parse diagram into two rows
    std::vector<std::string> rows;
    std::string row;
    for (char ch : diagram) {
        if (ch == '\n') {
            rows.push_back(row);
            row.clear();
        } else {
            row += ch;
        }
    }
    if (!row.empty()) {
        rows.push_back(row);
    }

    if (rows.size() != 2) {
        throw std::invalid_argument("Diagram must have two rows");
    }

    // Use default students if none provided
    std::vector<std::string> sorted_students = students.empty() ? default_students : students;
    std::sort(sorted_students.begin(), sorted_students.end());

    for (size_t i = 0; i < sorted_students.size(); ++i) {
        std::vector<Plants> plants;
        for (int r = 0; r < 2; ++r) {
            plants.push_back(char_to_plant(rows[r][2 * i]));
            plants.push_back(char_to_plant(rows[r][2 * i + 1]));
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

// Standalone function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    Garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
