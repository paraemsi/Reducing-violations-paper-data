#include "grade_school.h"

namespace grade_school {

bool school::add(const student_t& name, grade_t grade)
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

std::vector<student_t> school::grade(grade_t grade) const
{
    std::vector<student_t> result;
    auto it = m_grades.find(grade);
    if(it != m_grades.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<int, std::vector<std::string> > school::roster() const
{
    std::map<int, std::vector<std::string> > result;
    for(const auto& grade_entry : m_grades) {
        std::vector<std::string> students(grade_entry.second.begin(), grade_entry.second.end());
        result[static_cast<int>(grade_entry.first)] = students;
    }
    return result;
}

}  // namespace grade_school
