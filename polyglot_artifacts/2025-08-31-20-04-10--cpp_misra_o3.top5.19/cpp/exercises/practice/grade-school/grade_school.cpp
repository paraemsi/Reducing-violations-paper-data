#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, grade_type grade_level) {
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if ((std::find(students.begin(), students.end(), name)) != students.end()) {
            /* Student already enrolled – ignore duplicate */
            return;
        }
    }

    auto& students_in_grade = roster_[grade_level];
    students_in_grade.push_back(name);

    /* Keep students in alphabetical order */
    std::sort(students_in_grade.begin(), students_in_grade.end());
}

std::map<grade_type, std::vector<std::string>> school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(grade_type grade_level) const {
    const auto it = roster_.find(grade_level);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return {};
    }
}

}  // namespace grade_school
