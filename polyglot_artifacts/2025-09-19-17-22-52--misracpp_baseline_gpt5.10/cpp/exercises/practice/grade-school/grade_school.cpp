#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade_number) noexcept {
    if (all_students_.find(name) != all_students_.end()) {
        return false;
    }
    students_by_grade_[grade_number].insert(name);
    all_students_.insert(name);
    return true;
}

std::map<int, std::vector<std::string>> school::roster() const noexcept {
    std::map<int, std::vector<std::string>> result;
    for (const auto& kv : students_by_grade_) {
        result[kv.first] = std::vector<std::string>(kv.second.begin(), kv.second.end());
    }
    return result;
}

std::vector<std::string> school::grade(int grade_number) const noexcept {
    std::vector<std::string> result;
    auto it = students_by_grade_.find(grade_number);
    if (it != students_by_grade_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

}  // namespace grade_school
