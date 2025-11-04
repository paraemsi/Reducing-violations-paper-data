#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, grade_t grade)
{
    /* Duplicate detection: a student must not appear twice */
    for (const auto& grade_entry : m_roster)
    {
        const auto& students = grade_entry.second;
        if ((std::find(students.cbegin(), students.cend(), name) != students.cend()))
        {
            throw std::domain_error("Student already exists in roster");
        }
    }

    auto& students = m_roster[grade];
    students.push_back(name);

    /* Keep student list in alphabetical order */
    std::sort(students.begin(), students.end());
}

roster_t school::roster() const
{
    return m_roster; /* map is already grade-sorted */
}

std::vector<std::string> school::grade(grade_t grade) const
{
    const auto it = m_roster.find(grade);
    if (it != m_roster.end())
    {
        return it->second;
    }
    return {}; /* empty vector if grade not present */
}

}  // namespace grade_school
