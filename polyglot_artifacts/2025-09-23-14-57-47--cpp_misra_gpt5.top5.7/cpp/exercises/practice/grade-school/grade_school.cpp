#include "grade_school.h"

#include <utility>

namespace grade_school {

bool school::add(const std::string& name, grade_type grade)
{
    // Check global uniqueness across all grades.
    for (const auto& kv : m_roster) {
        const std::set<std::string>& names = kv.second;
        if ((names.find(name) != names.end())) {
            return false;
        }
    }
    (void)m_roster[grade].insert(name);
    return true;
}

std::vector<std::string> school::grade(grade_type grade) const
{
    std::vector<std::string> result {};
    const auto it = m_roster.find(grade);
    if ((it != m_roster.end())) {
        result.assign(it->second.begin(), it->second.end());
    } else {
        // No students in this grade.
    }
    return result;
}

school::roster_type school::roster() const
{
    roster_type out {};
    for (const auto& kv : m_roster) {
        std::vector<std::string> names {};
        names.assign(kv.second.begin(), kv.second.end());
        (void)out.emplace(kv.first, std::move(names));
    }
    return out;
}

}  // namespace grade_school
