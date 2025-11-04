#include "grade_school.h"

namespace grade_school {

bool school::add(const student_t& name, grade_t grade)
{
    // Check if student already exists
    if(m_all_students.find(name) != m_all_students.end()) {
        return false;
    }
    (m_grades[grade]).insert(name);
    m_all_students.insert(name);
    return true;
}

std::vector<student_t> school::grade(grade_t grade) const
{
    auto it = m_grades.find(grade);
    if(it != m_grades.end()) {
        return std::vector<student_t>((it->second).begin(), (it->second).end());
    }
    return std::vector<student_t>();
}

std::vector<student_t> school::roster() const
{
    std::vector<student_t> all;
    for(const auto& grade_entry : m_grades) {
        all.insert(all.end(), (grade_entry.second).begin(), (grade_entry.second).end());
    }
    return all;
}

std::map<grade_t, std::vector<student_t> > school::grades() const
{
    std::map<grade_t, std::vector<student_t> > result;
    for(const auto& grade_entry : m_grades) {
        result[grade_entry.first] = std::vector<student_t>(grade_entry.second.begin(), grade_entry.second.end());
    }
    return result;
}

}  // namespace grade_school
