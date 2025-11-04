#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, grade_t grade_level)
{
    /* Prevent duplicate student across all grades */
    for (auto& entry : m_roster) {
        const student_list_t& students_in_grade = entry.second;
        if (std::find(students_in_grade.cbegin(), students_in_grade.cend(), name) != students_in_grade.cend()) {
            /* Duplicate student detected – no modifications made */
            return;
        }
    }

    student_list_t& students = m_roster[grade_level];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

student_list_t school::grade(grade_t grade_level) const
{
    const auto iter = m_roster.find(grade_level);
    if (iter != m_roster.end()) {
        return iter->second;
    } else {
        return {};
    }
}

roster_t school::roster() const
{
    return m_roster;
}

}  // namespace grade_school
