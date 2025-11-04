#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_number) noexcept
{
    const auto insert_result = m_students.insert(name);
    if ((insert_result.second) == false)
    {
        return false;
    }

    auto& students_in_grade = m_roster[grade_number];
    students_in_grade.push_back(name);
    std::sort(students_in_grade.begin(), students_in_grade.end());

    return true;
}

std::vector<std::string> school::grade(grade_t grade_number) const noexcept
{
    const auto it = m_roster.find(grade_number);
    if ((it != m_roster.end()))
    {
        return it->second;
    }
    else
    {
        return {};
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const noexcept
{
    return m_roster;
}

}  // namespace grade_school
