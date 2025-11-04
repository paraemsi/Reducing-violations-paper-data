#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, grade_t grade_number)
{
    // If the student is already enrolled in any grade, exit early.
    for (const auto& grade_pair : m_roster_) {
        if (grade_pair.second.find(name) != grade_pair.second.end()) {
            return;  // Student already exists; no changes made.
        }
    }

    // Insert the student and maintain lexical order via std::set
    (void)m_roster_[grade_number].insert(name);
}

roster_t school::roster() const
{
    roster_t result{};

    for (const auto& grade_pair : m_roster_) {
        const auto& grade_set{grade_pair.second};
        std::vector<std::string> students{grade_set.begin(), grade_set.end()};
        result.emplace(grade_pair.first, students);
    }

    return result;
}

std::vector<std::string> school::grade(grade_t grade_number) const
{
    std::vector<std::string> students{};

    const auto grade_it{m_roster_.find(grade_number)};
    if (grade_it != m_roster_.end()) {
        const auto& grade_set{grade_it->second};
        students.assign(grade_set.begin(), grade_set.end());
    }

    return students;
}

}  // namespace grade_school
