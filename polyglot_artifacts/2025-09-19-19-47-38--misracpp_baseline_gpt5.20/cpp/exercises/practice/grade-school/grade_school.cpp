#include "grade_school.h"
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, grade_t grade) {
    // Do not add duplicates anywhere in the school (whether same grade or different).
    if (student_to_grade_.find(name) != student_to_grade_.end()) {
        throw std::invalid_argument("Student already exists in the roster");
    }
    grades_[grade].insert(name);
    student_to_grade_[name] = grade;
}

std::map<grade_t, std::vector<std::string>> school::roster() const {
    std::map<grade_t, std::vector<std::string>> result;
    for (const auto& entry : grades_) {
        const grade_t g = entry.first;
        const auto& names_set = entry.second;
        result[g] = std::vector<std::string>(names_set.begin(), names_set.end());
    }
    return result;
}

std::vector<std::string> school::grade(grade_t g) const {
    std::vector<std::string> result;
    auto it = grades_.find(g);
    if (it != grades_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

}  // namespace grade_school
