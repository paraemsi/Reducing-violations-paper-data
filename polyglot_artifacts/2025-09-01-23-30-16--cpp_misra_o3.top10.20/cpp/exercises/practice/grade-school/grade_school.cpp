#include "grade_school.h"

#include <algorithm>   // for std::find, std::sort

namespace grade_school {

auto school::add(const std::string& name, grade_type grade) -> bool
{
    // If the student is already present in any grade, do nothing.
    for (auto& entry : m_roster) {
        auto& students { entry.second };
        const auto pos { std::find(students.begin(), students.end(), name) };
        if (pos != students.end()) {
            return false;  // Student already enrolled.
        }
    }

    auto& students { m_roster[grade] };
    students.push_back(name);
    std::sort(students.begin(), students.end());
    return true;
}

auto school::grade(grade_type grade) const -> std::vector<std::string>
{
    const auto it { m_roster.find(grade) };
    if (it == m_roster.end()) {
        return {};
    } else {
        return it->second;
    }
}

auto school::roster() const -> roster_type
{
    return m_roster; // `std::map` already keeps grades sorted.
}


}  // namespace grade_school
