#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_t grade)
{
    // Check if student already exists
    if(m_name_to_grade.find(name) != m_name_to_grade.end()) {
        // Already present
        return false;
    }
    // Add to grade set and name map
    (void)m_roster[grade].insert(name);
    (void)m_name_to_grade.insert(std::make_pair(name, grade));
    return true;
}

std::vector<std::string> school::grade(grade_t grade) const
{
    std::vector<std::string> result;
    auto it = m_roster.find(grade);
    if(it != m_roster.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<int, std::vector<std::string> > school::roster() const
{
    std::map<int, std::vector<std::string> > result;
    for(const auto& entry : m_roster) {
        std::vector<std::string> names(entry.second.begin(), entry.second.end());
        result[static_cast<int>(entry.first)] = names;
    }
    return result;
}

}  // namespace grade_school
