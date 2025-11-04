#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

Garden::Garden(const std::string& diagram) {
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

void Garden::initialize_students() {
    students_ = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    std::sort(students_.begin(), students_.end());
}

void Garden::initialize_plant_map() {
    plant_map_['V'] = Plants::violets;
    plant_map_['R'] = Plants::radishes;
    plant_map_['C'] = Plants::clover;
    plant_map_['G'] = Plants::grass;
}

int Garden::student_index(const std::string& student) const {
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        throw std::out_of_range("Student not found");
    }
    return static_cast<int>(std::distance(students_.begin(), it));
}

std::vector<Plants> Garden::plants(const std::string& student) const {
    int idx = student_index(student);
    std::vector<Plants> result;
    for (const auto& row : rows_) {
        if (row.size() < (idx + 1) * 2) continue;
        result.push_back(plant_map_.at(row[idx * 2]));
        result.push_back(plant_map_.at(row[idx * 2 + 1]));
    }
    return result;
}

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    kindergarten_garden::Garden garden(diagram);
    return garden.plants(student);
}

}  // namespace kindergarten_garden
