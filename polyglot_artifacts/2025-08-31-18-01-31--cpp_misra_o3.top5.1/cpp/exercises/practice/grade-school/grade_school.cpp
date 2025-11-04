#include "grade_school.h"


namespace grade_school {

void school::add(const std::string& name, grade_t level)
{
    /*  Prevent duplicate enrolment.  If the student already exists in any
     *  grade, consider the request invalid and leave the roster unchanged. */
    for(const auto& pair : m_data)
    {
        if(pair.second.find(name) != pair.second.end())
        {
            return;
        }
    }

    /*  Insert the student into the requested grade.  The set guarantees the
     *  name is unique within the grade and keeps alphabetical order.        */
    (void)m_data[level].insert(name);
}

std::vector<std::string> school::grade(grade_t level) const
{
    const auto iter = m_data.find(level);
    if(iter == m_data.end())
    {
        return {};
    }
    return std::vector<std::string>(iter->second.begin(), iter->second.end());
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result{};
    for(const auto& pair : m_data)
    {
        result.emplace(pair.first,
                       std::vector<std::string>(pair.second.begin(),
                                                pair.second.end()));
    }
    return result;
}

}  // namespace grade_school
