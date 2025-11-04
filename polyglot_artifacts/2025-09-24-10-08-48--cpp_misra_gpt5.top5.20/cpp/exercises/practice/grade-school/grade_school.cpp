#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, grade_school::school::grade_type grade) {
    // Ensure the student does not already exist anywhere in the roster.
    for (const auto& entry : m_roster) {
        const auto& students = entry.second;
        if (std::binary_search(students.begin(), students.end(), name)) {
            return;
        }
    }

    auto& students_in_grade = m_roster[grade];
    const auto insert_pos = std::lower_bound(students_in_grade.begin(), students_in_grade.end(), name);
    if ((insert_pos != students_in_grade.end()) && ((*insert_pos) == name)) {
        // Defensive: should not be reached due to global check above.
        return;
    } else {
        students_in_grade.insert(insert_pos, name);
    }
}

std::map<school::grade_type, std::vector<std::string>> school::roster() const {
    return m_roster;
}

std::vector<std::string> school::grade(grade_school::school::grade_type grade) const {
    const auto it = m_roster.find(grade);
    if ((it != m_roster.end())) {
        return it->second;
    } else {
        return {};
    }
}

}  // namespace grade_school
