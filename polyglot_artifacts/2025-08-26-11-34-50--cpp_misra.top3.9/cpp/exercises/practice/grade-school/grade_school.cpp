#include "grade_school.h"

namespace grade_school {

bool school::add(const name_t& name, grade_t grade)
{
    // Check if student already exists
    if(m_all_students.find(name) != m_all_students.end()) {
        return false;
    }
    (m_roster[grade]).insert(name);
    (void)m_all_students.insert(name);
    return true;
}

std::vector<name_t> school::grade(grade_t grade) const
{
    std::vector<name_t> result;
    auto it = m_roster.find(grade);
    if(it != m_roster.end()) {
        result.assign((it->second).begin(), (it->second).end());
    }
    return result;
}

std::map<grade_t, std::vector<name_t> > school::roster() const
{
    std::map<grade_t, std::vector<name_t> > result;
    for(const auto& grade_entry : m_roster) {
        std::vector<name_t> students(grade_entry.second.begin(), grade_entry.second.end());
        result[grade_entry.first] = students;
    }
    return result;
}

}  // namespace grade_school
