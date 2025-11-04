#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check whether the student already exists in any grade.
    for (const auto& entry : students_) {
        if (entry.second.count(name) != 0) {
            return false;
        }
    }
    students_[grade].insert(name);
    return true;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& entry : students_) {
        const int g = entry.first;
        const auto& names = entry.second;
        result[g] = std::vector<std::string>(names.begin(), names.end());
    }
    return result;
}

std::vector<std::string> school::grade(int grade) const {
    const auto it = students_.find(grade);
    if (it == students_.end()) {
        return {};
    }
    return std::vector<std::string>(it->second.begin(), it->second.end());
}

}  // namespace grade_school
