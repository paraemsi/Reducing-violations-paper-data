#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already in any grade
    // We need to search through all grades to ensure the student doesn't exist
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        // Use binary search since each grade's list is always sorted
        if (std::binary_search(students.begin(), students.end(), name)) {
            throw std::runtime_error("Student already exists in the roster");
        }
    }
    
    // Add to the grade and insert in sorted order
    auto& grade_list = roster_[grade];
    // Find where to insert to maintain order
    auto it = std::lower_bound(grade_list.begin(), grade_list.end(), name);
    grade_list.insert(it, name);
}

std::vector<std::string> school::grade(std::uint32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    // The map is always ordered by key (grade number), and each vector is always sorted
    return roster_;
}

}  // namespace grade_school
