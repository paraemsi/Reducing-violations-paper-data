#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> kindergarten_garden::default_students = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

namespace {
    Plant char_to_plant(char c) {
        switch (c) {
            case 'V': return Plant::violets;
            case 'R': return Plant::radishes;
            case 'C': return Plant::clover;
            case 'G': return Plant::grass;
            default: throw std::invalid_argument("Unknown plant code");
        }
    }
}

kindergarten_garden::kindergarten_garden(
    const std::string& diagram,
    const std::vector<std::string>& students)
{
    const std::vector<std::string>& used_students =
        students.empty() ? default_students : students;

    // Parse diagram into two rows
    size_t pos = 0;
    std::vector<std::string> rows;
    size_t start = 0;
    for (char c : diagram) {
        if (c == '\n') {
            rows.push_back(diagram.substr(start, pos - start));
            start = pos + 1;
        }
        ++pos;
    }
    if (start < diagram.size()) {
        rows.push_back(diagram.substr(start));
    }

    if (rows.size() != 2) {
        throw std::invalid_argument("Diagram must have two rows");
    }

    // Copy and sort students alphabetically
    std::vector<std::string> sorted_students = used_students;
    std::sort(sorted_students.begin(), sorted_students.end());

    for (size_t i = 0; i < sorted_students.size(); ++i) {
        std::vector<Plant> plants;
        for (size_t row = 0; row < 2; ++row) {
            size_t idx = i * 2;
            if (idx + 1 >= rows[row].size()) {
                throw std::invalid_argument("Diagram row too short for students");
            }
            plants.push_back(char_to_plant(rows[row][idx]));
            plants.push_back(char_to_plant(rows[row][idx + 1]));
        }
        student_plants_[sorted_students[i]] = plants;
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
