#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_t grade) {
    // Check if name already exists in any grade
    for (const auto& pair : grades_) {
        if ((pair.second.count(name)) > 0U) {
            return false;
        }
    }
    // Add to the grade
    grades_[grade].insert(name);
    return true;
}

std::vector<std::string> school::grade(grade_t grade) const {
    auto it = grades_.find(grade);
    if (it != grades_.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return {};
}

std::map<grade_t, std::vector<std::string>> school::roster() const {
    std::map<grade_t, std::vector<std::string>> result;
    for (const auto& pair : grades_) {
        result[pair.first] = std::vector<std::string>(pair.second.begin(), pair.second.end());
    }
    return result;
}

}  // namespace grade_school
