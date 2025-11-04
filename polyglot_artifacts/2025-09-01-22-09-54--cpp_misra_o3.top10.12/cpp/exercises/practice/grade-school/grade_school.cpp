#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level)
{
    //  Reject duplicate student irrespective of grade.
    for (const auto& pair : m_data)
    {
        if (pair.second.find(name) != pair.second.end())
        {
            return false;
        }
    }

    (void)m_data[grade_level].insert(name);   //  insert() return value intentionally ignored
    return true;
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result;

    for (const auto& pair : m_data)
    {
        result[pair.first] = std::vector<std::string>(pair.second.begin(), pair.second.end());
    }

    return result;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    std::vector<std::string> result;

    const auto it = m_data.find(grade_level);
    if (it != m_data.end())
    {
        result.assign(it->second.begin(), it->second.end());
    }

    return result;
}

}  // namespace grade_school
