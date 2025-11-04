#include "grade_school.h"

namespace grade_school {

bool school::add(const name_t& student, grade_t grade)
{
    // Check if student already exists
    if(m_all_students.find(student) != m_all_students.end()) {
        return false;
    }
    (m_grades[grade]).insert(student);
    m_all_students.insert(student);
    return true;
}

std::vector<name_t> school::grade(grade_t grade) const
{
    std::vector<name_t> result;
    auto it = m_grades.find(grade);
    if(it != m_grades.end()) {
        result.assign((it->second).begin(), (it->second).end());
    }
    return result;
}

std::vector<name_t> school::roster() const
{
    std::vector<name_t> result;
    for(const auto& grade_entry : m_grades) {
        result.insert(result.end(), (grade_entry.second).begin(), (grade_entry.second).end());
    }
    return result;
}

std::map<int, std::vector<std::string>> school::grades() const
{
    std::map<int, std::vector<std::string>> result;
    for(const auto& grade_entry : m_grades) {
        std::vector<std::string> students((grade_entry.second).begin(), (grade_entry.second).end());
        result[static_cast<int>(grade_entry.first)] = students;
    }
    return result;
}

}  // namespace grade_school
