#include "grade_school.h"

namespace grade_school {

bool school::add(const student_t& name, grade_t grade)
{
    // Check if student already exists in any grade
    if(m_all_students.find(name) != m_all_students.end()) {
        return false;
    }
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

std::vector<student_t> school::roster() const
{
    std::vector<student_t> result;
    for(const auto& grade_entry : m_grades) {
        result.insert(result.end(), grade_entry.second.begin(), grade_entry.second.end());
    }
    return result;
}

// Return a map of all grades to their students (for test compatibility)
std::map<int, std::vector<std::string> > school::grades() const
{
    std::map<int, std::vector<std::string> > result;
    for(const auto& entry : m_grades) {
        std::vector<std::string> students(entry.second.begin(), entry.second.end());
        result[static_cast<int>(entry.first)] = students;
    }
    return result;
}

}  // namespace grade_school
