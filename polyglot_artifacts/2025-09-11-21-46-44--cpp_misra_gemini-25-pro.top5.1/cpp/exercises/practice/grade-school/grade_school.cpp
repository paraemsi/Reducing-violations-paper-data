#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    std::int32_t old_grade = -1;

    for (auto& pair : student_roster) {
        auto& students = pair.second;
        auto it = std::find(students.begin(), students.end(), name);

        if (it != students.end()) {
            // Student is already in the roster.
            if (pair.first == grade) {
                // Already in the correct grade.
                return;
            }
            // In a different grade. Remove from old grade.
            old_grade = pair.first;
            students.erase(it);
            break;
        }
    }

    // If student was moved, the old grade might be empty.
    if (old_grade != -1) {
        if (student_roster.at(old_grade).empty()) {
            student_roster.erase(old_grade);
        }
    }

    // Add student to new grade.
    student_roster[grade].push_back(name);
    std::sort(student_roster[grade].begin(), student_roster[grade].end());
}

std::vector<std::string> school::grade(std::int32_t grade_num) const {
    auto const it = student_roster.find(grade_num);
    if (it != student_roster.end()) {
        return it->second;
    }

    return {};
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    return student_roster;
}

}  // namespace grade_school
