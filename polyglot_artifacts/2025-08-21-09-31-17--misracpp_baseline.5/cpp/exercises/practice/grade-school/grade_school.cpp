#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if student already exists in any grade
    for (const auto& [g, names] : students_by_grade_) {
        if (names.count(name) > 0) {
            return false; // Student already present
        }
    }
    students_by_grade_[grade].insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> result;
    auto it = students_by_grade_.find(grade);
    if (it != students_by_grade_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::vector<std::string> school::roster() const {
    std::vector<std::string> result;
    for (const auto& [grade, names] : students_by_grade_) {
        result.insert(result.end(), names.begin(), names.end());
    }
    return result;
}

}  // namespace grade_school
