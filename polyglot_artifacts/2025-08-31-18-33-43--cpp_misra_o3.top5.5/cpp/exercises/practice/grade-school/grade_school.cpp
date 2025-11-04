#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level)
{
    /* Check if the student already exists in any grade */
    for (auto const& grade_entry : roster_) {
        for (auto const& student : grade_entry.second) {
            if (student == name) {
                return false;
            }
        }
    }

    auto& students = roster_[grade_level];
    students.push_back(name);
    std::sort(students.begin(), students.end());
    return true;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    auto const it = roster_.find(grade_level);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return {};
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    return roster_;
}

}  // namespace grade_school
