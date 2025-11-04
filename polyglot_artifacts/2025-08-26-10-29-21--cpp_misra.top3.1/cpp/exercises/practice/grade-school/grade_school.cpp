#include "grade_school.h"

namespace grade_school {

bool school::add(const student_t& name, grade_t grade)
{
    // Check if student already exists in any grade
    for(const auto& entry : m_roster) {
        if((entry.second).find(name) != (entry.second).end()) {
            // Student already present in some grade
            return false;
        }
    }
    // Insert student into the correct grade
    (m_roster[grade]).insert(name);
    return true;
}

std::vector<student_t> school::grade(grade_t grade) const
{
    std::vector<student_t> result;
    auto it = m_roster.find(grade);
    if(it != m_roster.end()) {
        result.assign((it->second).begin(), (it->second).end());
    }
    return result;
}

std::map<int, std::vector<student_t>> school::roster() const
{
    std::map<int, std::vector<student_t>> result;
    for(const auto& entry : m_roster) {
        result[static_cast<int>(entry.first)] = std::vector<student_t>((entry.second).begin(), (entry.second).end());
    }
    return result;
}

}  // namespace grade_school
