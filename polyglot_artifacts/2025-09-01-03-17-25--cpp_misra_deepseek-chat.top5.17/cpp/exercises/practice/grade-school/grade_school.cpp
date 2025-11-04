#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // First, check if the student exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        // Since each grade's list is always sorted, we can use binary search
        if (std::binary_search(students.begin(), students.end(), name)) {
            // Student found, don't add
            return;
        }
    }
    
    // Find the grade to add to, or create it if it doesn't exist
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        // Grade exists, insert the name in sorted order
        auto& students_in_grade = it->second;
        students_in_grade.insert(
            std::upper_bound(students_in_grade.begin(), students_in_grade.end(), name),
            name
        );
    } else {
        // Grade doesn't exist, create new vector with the name
        roster_[grade] = std::vector<std::string>{name};
    }
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
