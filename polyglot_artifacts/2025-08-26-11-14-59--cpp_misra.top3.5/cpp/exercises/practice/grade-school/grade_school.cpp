#include "grade_school.h"

namespace grade_school {

bool school::add(const student_t& name, grade_t grade)
{
    // Check if student already exists in any grade
    if(m_all_students.find(name) != m_all_students.end()) {
        return false;
    }
    (m_grades[grade]).insert(name);
    m_all_students.insert(name);
    return true;
}

std::vector<student_t> school::grade(grade_t grade) const
{
    std::vector<student_t> result;
    auto it = m_grades.find(grade);
    if(it != m_grades.end()) {
        result.assign((it->second).begin(), (it->second).end());
    }
    return result;
}

std::vector<student_t> school::roster() const
{
    std::vector<student_t> result;
    for(const auto& grade_entry : m_grades) {
        result.insert(result.end(), (grade_entry.second).begin(), (grade_entry.second).end());
    }
    return result;
}

}  // namespace grade_school
