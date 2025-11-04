#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Disallow duplicates across the entire roster.
    if (all_students_.find(name) != all_students_.end()) {
        return false;
    }
    data_[grade].insert(name);
    all_students_.insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> students;
    auto it = data_.find(grade);
    if (it != data_.end()) {
        students.assign(it->second.begin(), it->second.end());
    }
    return students;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& entry : data_) {
        const auto& grade = entry.first;
        const auto& names = entry.second;
        result[grade] = std::vector<std::string>(names.begin(), names.end());
    }
    return result;
}

}  // namespace grade_school
