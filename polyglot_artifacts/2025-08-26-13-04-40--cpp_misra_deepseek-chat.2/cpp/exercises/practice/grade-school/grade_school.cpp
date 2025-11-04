#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

school::school() : roster_() {}

void school::add(const std::string& name, int grade) {
    // Cast to grade_t to comply with MISRA rules
    grade_t fixed_grade = static_cast<grade_t>(grade);
    
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::runtime_error("Student already exists");
        }
    }
    
    // Add the student to the specified grade
    auto& grade_students = roster_[fixed_grade];
    grade_students.push_back(name);
    // Sort the students in the grade alphabetically
    std::sort(grade_students.begin(), grade_students.end());
}

const std::map<grade_t, std::vector<std::string>>& school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(int grade) const {
    // Cast to grade_t to comply with MISRA rules
    grade_t fixed_grade = static_cast<grade_t>(grade);
    auto it = roster_.find(fixed_grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
