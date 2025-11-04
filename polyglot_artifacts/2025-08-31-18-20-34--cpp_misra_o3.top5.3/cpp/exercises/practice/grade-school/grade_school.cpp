#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_type grade)
{
    /* Check for duplicate in any grade */
    for (const auto& pair : m_roster) {
        const auto& students{pair.second};
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            return false;
        }
    }

    std::vector<std::string>& students_in_grade = m_roster[grade];
    students_in_grade.push_back(name);

    /* Keep names alphabetically ordered */
    std::sort(students_in_grade.begin(), students_in_grade.end());

    return true;
}

std::map<school::grade_type, std::vector<std::string>> school::roster() const
{
    return m_roster; /* std::map keeps grades ordered ascending */
}

std::vector<std::string> school::grade(grade_type grade_number) const
{
    const auto it{m_roster.find(grade_number)};
    if (it != m_roster.end()) {
        return it->second;
    } else {
        return {};
    }
}

}  // namespace grade_school
