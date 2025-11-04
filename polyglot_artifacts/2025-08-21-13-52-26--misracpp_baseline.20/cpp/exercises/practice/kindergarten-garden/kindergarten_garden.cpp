#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

kindergarten_garden::kindergarten_garden(const std::string& diagram) {
    // Split diagram into rows
    size_t pos = 0, prev = 0;
    while ((pos = diagram.find('\n', prev)) != std::string::npos) {
        rows_.push_back(diagram.substr(prev, pos - prev));
        prev = pos + 1;
    }
    if (prev < diagram.size()) {
        rows_.push_back(diagram.substr(prev));
    }

    initialize_students();
    initialize_plant_map();
}

void kindergarten_garden::initialize_students() {
    students_ = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    std::sort(students_.begin(), students_.end());
}

void kindergarten_garden::initialize_plant_map() {
    plant_map_['G'] = Plant::grass;
    plant_map_['C'] = Plant::clover;
    plant_map_['R'] = Plant::radishes;
    plant_map_['V'] = Plant::violets;
}

int kindergarten_garden::student_index(const std::string& student) const {
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        throw std::invalid_argument("Unknown student: " + student);
    }
    return static_cast<int>(std::distance(students_.begin(), it));
}

std::vector<Plant> kindergarten_garden::plants(const std::string& student) const {
    int idx = student_index(student);
    std::vector<Plant> result;
    for (const auto& row : rows_) {
        if (static_cast<size_t>(2 * idx + 1) < row.size()) {
            result.push_back(plant_map_.at(row[2 * idx]));
            result.push_back(plant_map_.at(row[2 * idx + 1]));
        }
    }
    return result;
}

}  // namespace kindergarten_garden

// Free function for test compatibility
std::vector<kindergarten_garden::Plant> kindergarten_garden::plants(const std::string& diagram, const std::string& student) {
    kindergarten_garden::kindergarten_garden garden(diagram);
    return garden.plants(student);
}
