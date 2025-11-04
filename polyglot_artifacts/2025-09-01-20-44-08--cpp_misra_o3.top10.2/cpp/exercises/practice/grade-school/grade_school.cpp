#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::insert_sorted(std::vector<std::string>& vec,
                           const std::string&        name)
{
    auto const it = std::lower_bound(vec.begin(), vec.end(), name);
    (void)vec.insert(it, name); /* value intentionally ignored */
}

void school::add(const std::string& name, grade_t grade_level)
{
    /* Ensure the student is not already present in any grade */
    for (auto& pair : m_roster) {
        auto const& students = pair.second;
        if ((std::find(students.begin(), students.end(), name)) != students.end()) {
            return;
        }
    }

    /* Insert the student into the requested grade, keeping names sorted */
    auto& students = m_roster[grade_level];
    if ((std::find(students.begin(), students.end(), name)) == students.end()) {
        insert_sorted(students, name);
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    return m_roster;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    auto const it = m_roster.find(grade_level);
    if (it != m_roster.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
