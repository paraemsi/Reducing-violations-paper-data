#include "grade_school.h"

namespace grade_school {

bool school::add(const student_name& name, grade_t grade)
{
    // Check if student already exists in any grade
    if(m_all_students.find(name) != m_all_students.end()) {
        return false;
    }
    // Insert student into the grade
    (void)m_grades[grade].insert(name);
    (void)m_all_students.insert(name);
    return true;
}

std::vector<student_name> school::grade(grade_t grade) const
{
    std::vector<student_name> result;
    auto it = m_grades.find(grade);
    if(it != m_grades.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<grade_t, std::vector<student_name> > school::roster() const
{
    std::map<grade_t, std::vector<student_name> > result;
    for(const auto& grade_entry : m_grades) {
        result[grade_entry.first] = std::vector<student_name>(grade_entry.second.begin(), grade_entry.second.end());
    }
    return result;
}

}  // namespace grade_school
