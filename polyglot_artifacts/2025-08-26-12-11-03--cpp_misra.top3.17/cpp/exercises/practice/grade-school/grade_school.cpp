#include "grade_school.h"

namespace grade_school {

bool school::add(const name_t& student, grade_t grade)
{
    // Check if student already exists
    if(m_student_grade.find(student) != m_student_grade.end()) {
        // Student already present, do not add again
        return false;
    }
    // Add student to grade
    m_roster[grade].insert(student);
    m_student_grade[student] = grade;
    return true;
}

std::vector<name_t> school::grade(grade_t grade) const
{
    std::vector<name_t> students;
    auto it = m_roster.find(grade);
    if(it != m_roster.end()) {
        students.assign(it->second.begin(), it->second.end());
    }
    return students;
}

std::map<int, std::vector<name_t>> school::roster() const
{
    std::map<int, std::vector<name_t>> result;
    for(const auto& entry : m_roster) {
        result[static_cast<int>(entry.first)] = std::vector<name_t>(entry.second.begin(), entry.second.end());
    }
    return result;
}

}  // namespace grade_school
