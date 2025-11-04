#include "grade_school.h"

#include <algorithm>   /* for std::sort */
#include <stdexcept>   /* for std::invalid_argument */

namespace grade_school {

/* ------------------------------------------------------------------------- */
/* private helper                                                            */
bool school::already_enrolled(const std::string& name) const
{
    /* Search every grade for the student name.                              */
    for (const auto& grade_entry : m_roster) {
        const auto& students = grade_entry.second;
        if (std::find(students.cbegin(), students.cend(), name) != students.cend()) {
            return true;
        }
    }
    return false;
}

/* ------------------------------------------------------------------------- */
/* public interface                                                          */
void school::add(const std::string& name, grade_t grade_level)
{
    if (already_enrolled(name)) {
        throw std::invalid_argument("student already enrolled");
    }

    /* Insert or append, then keep the vector sorted alphabetically.         */
    auto& students = m_roster[grade_level];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    const auto it = m_roster.find(grade_level);
    if (it != m_roster.cend()) {
        return it->second;
    } else {
        return {};
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    return m_roster;
}

}  // namespace grade_school
