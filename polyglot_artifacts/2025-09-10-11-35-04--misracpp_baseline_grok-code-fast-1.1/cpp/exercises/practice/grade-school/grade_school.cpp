#include "grade_school.h"
#include <set>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    if (all_students_.count(name)) {
        return false;  // Student already enrolled
    }
    all_students_.insert(name);
    students_[grade].insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = students_.find(grade);
    if (it != students_.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return {};
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& p : students_) {
        result[p.first] = std::vector<std::string>(p.second.begin(), p.second.end());
    }
    return result;
}

}  // namespace grade_school
