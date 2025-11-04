#include "grade_school.h"
#include <cstddef>

namespace grade_school {

auto school::add(const std::string& name, grade_t grade) -> bool
{
    for (const auto& kv : m_data)
    {
        const auto& students = kv.second;
        if (students.count(name) != static_cast<std::size_t>(0U))
        {
            return false;
        }
    }

    m_data[grade].insert(name);
    return true;
}

auto school::grade(grade_t grade) const -> std::vector<std::string>
{
    std::vector<std::string> result {};
    const auto it = m_data.find(grade);

    if (it != m_data.end())
    {
        result.assign(it->second.begin(), it->second.end());
    }

    return result;
}

auto school::roster() const -> std::map<grade_t, std::vector<std::string>>
{
    std::map<grade_t, std::vector<std::string>> result {};

    for (const auto& kv : m_data)
    {
        result[kv.first].assign(kv.second.begin(), kv.second.end());
    }

    return result;
}

}  // namespace grade_school
