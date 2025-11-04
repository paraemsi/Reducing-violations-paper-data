#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, grade_t grade) {
    // Indicate error if student already exists anywhere in the roster.
    if (students_.find(name) != students_.end()) {
        throw std::invalid_argument("student already enrolled");
    }
    students_.insert(name);
    auto& students_in_grade = roster_[grade];
    students_in_grade.push_back(name);
    std::sort(students_in_grade.begin(), students_in_grade.end());
}

std::vector<std::string> school::grade(grade_t grade) const {
    auto it = roster_.find(grade);
    if (it == roster_.end()) {
        return {};
    }
    return it->second; // already kept sorted on insert
}

roster_t school::roster() const {
    // Ensure all grade lists are sorted (defensive)
    roster_t result = roster_;
    for (auto& entry : result) {
        std::vector<std::string>& students = entry.second;
        std::sort(students.begin(), students.end());
    }
    return result;
}

}  // namespace grade_school
