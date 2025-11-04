#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade)
{
    /* Ignore duplicate student names (specification requirement) */
    if(m_student_grade.find(name) != m_student_grade.end())
    {
        return;
    }

    /* Record student->grade mapping */
    m_student_grade[name] = grade;

    /* Insert the student into the grade roster and keep it sorted */
    auto& students = m_grade_roster[grade];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

std::vector<std::string> school::grade(std::int32_t grade) const
{
    const auto it = m_grade_roster.find(grade);
    if(it != m_grade_roster.end())
    {
        return it->second;
    }
    return {};
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const
{
    return m_grade_roster;
}

}  // namespace grade_school
