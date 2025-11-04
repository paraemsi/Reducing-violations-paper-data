#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Ignore the request if the student is already enrolled in any grade.
    for (const auto& [g, names_set] : students_) {
        if (names_set.find(name) != names_set.end()) {
            return;
        }
    }
    students_[grade].insert(name);
}

std::vector<std::string> school::grade(int grade) const {
    auto it = students_.find(grade);
    if (it == students_.end()) {
        return {};
    }
    return std::vector<std::string>(it->second.begin(), it->second.end());
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& [grade, names_set] : students_) {
        result.emplace(grade, std::vector<std::string>(names_set.begin(), names_set.end()));
    }
    return result;
}

}  // namespace grade_school
