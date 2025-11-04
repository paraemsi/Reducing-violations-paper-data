#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, grade_t grade_level)
{
    // Reject duplicate students already present in any grade.
    for (auto & roster_entry : m_roster) {
        auto & students = roster_entry.second;
        if (students.find(name) != students.end()) {
            return; // Duplicate detected – no changes applied.
        }
    }

    // Insert the student; std::set keeps names sorted automatically.
    (void)m_roster[grade_level].insert(name);
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    const auto it = m_roster.find(grade_level);
    if (it == m_roster.end()) {
        return {}; // No such grade.
    }

    return std::vector<std::string>{it->second.begin(), it->second.end()};
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> full_roster {};

    for (const auto & roster_entry : m_roster) {
        const grade_t grade_key = roster_entry.first;
        const auto & students_set = roster_entry.second;
        full_roster.emplace(
            grade_key,
            std::vector<std::string>{students_set.begin(), students_set.end()});
    }

    return full_roster;
}

}  // namespace grade_school
