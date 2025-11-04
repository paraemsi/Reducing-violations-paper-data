#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level)
{
    // Reject duplicate student
    if (m_all_students.find(name) != m_all_students.end())
    {
        return false;
    }

    (void)m_all_students.insert(name);
    (void)m_roster[grade_level].insert(name);
    return true;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    std::vector<std::string> result{};
    auto const grade_it = m_roster.find(grade_level);
    if (grade_it != m_roster.end())
    {
        result.assign(grade_it->second.begin(), grade_it->second.end());
    }
    return result;
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result{};
    for (auto const& grade_entry : m_roster)
    {
        std::vector<std::string> names{};
        names.assign(grade_entry.second.begin(), grade_entry.second.end());
        result.emplace(grade_entry.first, std::move(names));
    }
    return result;
}

}  // namespace grade_school
