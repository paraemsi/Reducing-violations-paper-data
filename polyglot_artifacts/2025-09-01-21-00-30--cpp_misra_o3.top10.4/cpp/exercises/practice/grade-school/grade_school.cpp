#include "grade_school.h"

#include <algorithm>
#include <utility>

namespace grade_school {

bool school::add(std::string_view name, school::grade_t level)
{
    // Check if the student already exists in any grade.
    for (const auto &entry : m_roster) {
        if (entry.second.find(std::string{name}) != entry.second.end()) {
            return false;
        }
    }

    // Insert the student into the specified grade.
    (void)m_roster[level].insert(std::string{name});
    return true;
}

std::map<school::grade_t, std::vector<std::string>> school::roster() const
{
    std::map<school::grade_t, std::vector<std::string>> roster_out{};

    for (const auto &entry : m_roster) {
        roster_out.emplace(
            entry.first,
            std::vector<std::string>(entry.second.begin(), entry.second.end()));
    }

    return roster_out;
}

std::vector<std::string> school::grade(school::grade_t level) const
{
    const auto it = m_roster.find(level);
    if (it == m_roster.end()) {
        return {};
    } else {
        return std::vector<std::string>(it->second.begin(),
                                        it->second.end());
    }
}

}  // namespace grade_school
