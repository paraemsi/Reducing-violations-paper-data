#include "grade_school.h"

#include <algorithm>

namespace grade_school {

auto school::add(const std::string& name, grade_t grade) -> bool
{
    for(const auto& roster_entry : m_roster)
    {
        const auto& students_list = roster_entry.second;
        if(std::find(students_list.cbegin(), students_list.cend(), name) != students_list.cend())
        {
            return false;
        }
    }

    auto& students = m_roster[grade];
    students.push_back(name);
    std::sort(students.begin(), students.end());

    return true;
}

auto school::grade(grade_t grade) const -> std::vector<std::string>
{
    const auto iterator = m_roster.find(grade);
    if(iterator != m_roster.cend())
    {
        return iterator->second;
    }
    return {};
}

auto school::roster() const -> std::map<grade_t, std::vector<std::string>>
{
    return m_roster;
}

}  // namespace grade_school
