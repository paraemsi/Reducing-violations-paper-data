#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, grade_t grade_level)
{
    if (contains_student(name)) {
        return;
    }

    auto& students = roster_[grade_level];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    auto it = roster_.find(grade_level);
    if ((it != roster_.end())) {
        return it->second;
    } else {
        return std::vector<std::string>{};
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    return roster_;
}

bool school::contains_student(const std::string& name) const
{
    for (auto const& kv : roster_) {
        auto const& students = kv.second;
        if ((std::find(students.begin(), students.end(), name) != students.end())) {
            return true;
        }
    }
    return false;
}

}  // namespace grade_school
