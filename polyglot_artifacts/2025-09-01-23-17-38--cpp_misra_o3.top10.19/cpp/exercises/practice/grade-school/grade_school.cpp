#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_t grade)
{
    /* Check for the student's presence in any grade first. */
    for (const auto& grade_entry : m_roster) {
        const std::set<std::string>& students { grade_entry.second };
        if (students.find(name) != students.end()) {
            return false;
        }
    }

    /* Insert the student – the sub-script operator creates the set if needed. */
    (void)m_roster[grade].insert(name);
    return true;
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result {};

    for (const auto& grade_entry : m_roster) {
        grade_t grade_number { grade_entry.first };
        const std::set<std::string>& students_set { grade_entry.second };
        result[grade_number] = std::vector<std::string>(students_set.begin(), students_set.end());
    }

    return result;
}

std::vector<std::string> school::grade(grade_t grade) const
{
    const auto iterator { m_roster.find(grade) };
    if (iterator == m_roster.end()) {
        return {};
    }

    const std::set<std::string>& students_set { iterator->second };
    return std::vector<std::string>(students_set.begin(), students_set.end());
}

}  // namespace grade_school
