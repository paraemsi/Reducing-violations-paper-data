#include "grade_school.h"

namespace grade_school {

bool school::add(const student_name& name, grade_t grade)
{
    // Check if student already exists in any grade
    if(m_all_students.find(name) != m_all_students.end()) {
        return false;
    }
    // Insert student into grade and all_students set
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
    for (typename std::map<grade_t, std::set<student_name> >::const_iterator it = m_grades.begin(); it != m_grades.end(); ++it) {
        result[it->first] = std::vector<student_name>(it->second.begin(), it->second.end());
    }
    return result;
}

}  // namespace grade_school
