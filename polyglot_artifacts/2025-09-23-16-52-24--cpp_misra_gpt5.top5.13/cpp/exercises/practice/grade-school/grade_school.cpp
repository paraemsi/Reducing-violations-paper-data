#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::contains_student(const std::string& name) const
{
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if ((std::find(students.begin(), students.end(), name) != students.end())) {
            return true;
        }
    }
    return false;
}

void school::add(const std::string& name, int grade)
{
    if (!contains_student(name)) {
        auto& students = roster_[grade];
        students.push_back(name);
        std::sort(students.begin(), students.end());
    } else {
        // Duplicate across the roster: ignore as per requirements
    }
}

std::map<int, std::vector<std::string>> school::roster() const
{
    return roster_;
}

std::vector<std::string> school::grade(int grade) const
{
    const auto it = roster_.find(grade);
    if ((it != roster_.end())) {
        return it->second;
    } else {
        return std::vector<std::string>{};
    }
}

}  // namespace grade_school
