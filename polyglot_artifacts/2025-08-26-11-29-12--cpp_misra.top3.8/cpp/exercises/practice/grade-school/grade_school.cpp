#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade)
{
    // Check if student already exists
    if(m_student_grade.find(name) != m_student_grade.end()) {
        // Student already present
        return false;
    }
    // Add student to grade
    m_roster[grade].insert(name);
    m_student_grade[name] = grade;
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

std::map<grade_t, std::vector<std::string> > school::roster() const
{
    std::map<grade_t, std::vector<std::string> > result;
    for(const auto& entry : m_roster) {
        std::vector<std::string> names(entry.second.begin(), entry.second.end());
        result[entry.first] = names;
    }
    return result;
}

}  // namespace grade_school
