#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade_level) {
    // Prevent adding the same student more than once to the roster (any grade).
    for (const auto& entry : students_by_grade_) {
        if (entry.second.find(name) != entry.second.end()) {
            return false; // Duplicate addition is incorrect.
        }
    }
    students_by_grade_[grade_level].insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade_level) const {
    std::vector<std::string> result;
    auto it = students_by_grade_.find(grade_level);
    if (it != students_by_grade_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& entry : students_by_grade_) {
        result.emplace(entry.first, std::vector<std::string>(entry.second.begin(), entry.second.end()));
    }
    return result;
}

}  // namespace grade_school
