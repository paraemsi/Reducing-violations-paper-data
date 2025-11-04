#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if student already exists in any grade
    if (all_students_.count(name) > 0) {
        return false;
    }
    students_by_grade_[grade].insert(name);
    all_students_.insert(name);
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

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& grade_students : students_by_grade_) {
        result[grade_students.first] = std::vector<std::string>(grade_students.second.begin(), grade_students.second.end());
    }
    return result;
}

}  // namespace grade_school
