#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

auto school::add(const std::string& name, grade_t grade_level) -> void
{
    for (auto const& grade_students_pair : m_roster) {
        auto const& students = grade_students_pair.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::domain_error{"Student already in roster"};
        }
    }

    auto& students = m_roster[grade_level];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

auto school::grade(grade_t grade_level) const -> std::vector<std::string>
{
    auto const it = m_roster.find(grade_level);
    if ((it != m_roster.end())) {
        return it->second;
    } else {
        return {};
    }
}

auto school::roster() const -> std::map<grade_t, std::vector<std::string>>
{
    return m_roster;
}

}  // namespace grade_school
