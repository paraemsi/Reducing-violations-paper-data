#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, grade_t grade) {
    // Check if the student is already in the grade
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        const auto& students = it->second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::runtime_error("Student already exists in this grade");
        }
    }
    
    // Add the student to the grade
    roster_[grade].push_back(name);
    // Sort the students in the grade alphabetically
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

const std::map<grade_t, std::vector<std::string>>& school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(grade_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
