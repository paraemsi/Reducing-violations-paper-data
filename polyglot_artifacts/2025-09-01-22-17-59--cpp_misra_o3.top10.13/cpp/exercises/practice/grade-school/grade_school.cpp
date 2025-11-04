#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, grade_t grade_level_param)
{
    /*  Ensure the student is not already present in any grade.   */
    for (auto& [level, students] : m_roster) {
        if (students.find(name) != students.end()) {
            /*  Student already present – nothing to do.  */
            return;
        }
    }

    m_roster[grade_level_param].insert(name);
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    auto it = m_roster.find(grade_level);
    if (it == m_roster.end()) {
        return {};
    }

    return std::vector<std::string>(it->second.begin(), it->second.end());
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result {};
    for (auto const& [grade_level, students_set] : m_roster) {
        result.emplace(grade_level,
                       std::vector<std::string>(students_set.begin(),
                                                students_set.end()));
    }
    return result;
}

}  // namespace grade_school
