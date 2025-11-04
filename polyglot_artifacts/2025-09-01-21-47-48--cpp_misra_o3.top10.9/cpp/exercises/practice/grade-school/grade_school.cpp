#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_id)
{
    if(m_all_students_.find(name) != m_all_students_.end())
    {
        return false;
    }
    else
    {
        (void)m_all_students_.insert(name);
        (void)m_grades_[grade_id].insert(name);
        return true;
    }
}

std::vector<std::string> school::grade(grade_t grade_id) const
{
    std::vector<std::string> students{};

    const auto grade_it{m_grades_.find(grade_id)};
    if(grade_it != m_grades_.end())
    {
        students.assign(grade_it->second.begin(), grade_it->second.end());
    }

    return students;
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> full_roster{};

    for(const auto& grade_entry : m_grades_)
    {
        full_roster[grade_entry.first] =
            std::vector<std::string>(grade_entry.second.begin(), grade_entry.second.end());
    }

    return full_roster;
}

}  // namespace grade_school
