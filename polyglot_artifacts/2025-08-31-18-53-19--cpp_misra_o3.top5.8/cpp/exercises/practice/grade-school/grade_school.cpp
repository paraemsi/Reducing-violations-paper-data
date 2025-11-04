#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(std::string const& name, grade_t grade)
{
    /* Prevent duplicate student entries across all grades. */
    for (auto const& kv : m_roster) {
        auto const& students_ref = kv.second;
        if (std::find(students_ref.begin(), students_ref.end(), name) != students_ref.end()) {
            /* Student already present; per specification the request is ignored. */
            return;
        }
    }

    auto& students = m_roster[grade];
    students.push_back(name);
    std::sort(students.begin(), students.end()); /* maintain alphabetical order */
}

roster_t school::roster() const
{
    roster_t sorted_roster = m_roster;

    for (auto& kv : sorted_roster) {
        auto& students_ref = kv.second;
        std::sort(students_ref.begin(), students_ref.end());
    }

    return sorted_roster;
}

std::vector<std::string> school::grade(grade_t grade) const
{
    auto const it = m_roster.find(grade);

    if (it == m_roster.end()) {
        return {};
    } else {
        std::vector<std::string> students = it->second;
        std::sort(students.begin(), students.end());
        return students;
    }
}

}  // namespace grade_school
