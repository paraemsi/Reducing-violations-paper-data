#include "grade_school.h"

#include <algorithm>

namespace grade_school {

auto school::add(std::string const& name, grade_t grade) -> void
{
    /* Check for existing student in any grade */
    for (auto const& entry : m_data)
    {
        if (entry.second.find(name) != entry.second.end())
        {
            /* Duplicate detected – do not add again */
            return;
        }
    }

    /* Insert the student into the requested grade */
    (void)m_data[grade].insert(name);
}

auto school::grade(grade_t grade) const -> std::vector<std::string>
{
    auto const it { m_data.find(grade) };
    if (it == m_data.cend())
    {
        return {};
    }

    return { it->second.cbegin(), it->second.cend() };
}

auto school::roster() const -> std::map<grade_t, std::vector<std::string>>
{
    std::map<grade_t, std::vector<std::string>> result {};

    for (auto const& entry : m_data)
    {
        result.emplace(entry.first,
                       std::vector<std::string>{ entry.second.cbegin(),
                                                 entry.second.cend() });
    }

    return result;
}

}  // namespace grade_school
