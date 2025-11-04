#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Ensure the student isn't already enrolled in any grade.
    for (const auto& entry : students_) {
        if (entry.second.find(name) != entry.second.end()) {
            return;  // Duplicate – do nothing.
        }
    }
    students_[grade].insert(name);  // std::set keeps names alphabetically sorted.
}

std::vector<std::string> school::grade(int grade) const {
    auto it = students_.find(grade);
    if (it == students_.end()) {
        return {};
    }
    return {it->second.begin(), it->second.end()};
}

school::roster_t school::roster() const {
    roster_t result;
    for (const auto& entry : students_) {
        int g = entry.first;
        const auto& names = entry.second;
        result.emplace(g, std::vector<std::string>{names.begin(), names.end()});
    }
    return result;
}

}  // namespace grade_school
