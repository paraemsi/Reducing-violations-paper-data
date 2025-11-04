#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, grade_t grade) {
    // First, check if the student is already in the target grade
    const auto grade_it = roster_.find(grade);
    if (grade_it != roster_.end()) {
        const auto& students_in_grade = grade_it->second;
        if (std::find(students_in_grade.begin(), students_in_grade.end(), name) != students_in_grade.end()) {
            throw std::runtime_error("Student already exists in this grade");
        }
    }
    
    // Check if the student exists in any other grade
    for (const auto& entry : roster_) {
        if (entry.first != grade) {
            const auto& students = entry.second;
            if (std::find(students.begin(), students.end(), name) != students.end()) {
                throw std::runtime_error("Student already exists in another grade");
            }
        }
    }
    
    // Add to the appropriate grade
    auto& students = roster_[grade];
    // Insert in sorted order
    auto it = std::lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
}

std::vector<std::string> school::grade(grade_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) { 
        return it->second;
    } else { 
        return {};
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
