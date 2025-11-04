#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

bool school::student_exists(const std::string& name) const
{
    for (const auto& grade_pair : roster_) {
        const auto& students = grade_pair.second;
        if (std::find(std::begin(students), std::end(students), name) != std::end(students)) {
            return true;
        }
    }
    return false;
}

void school::add(const std::string& name, grade_t grade)
{
    if (student_exists(name)) {
        throw std::invalid_argument("student already added");
    }

    auto& students = roster_[grade];
    students.push_back(name);
    std::sort(std::begin(students), std::end(students));
}

std::vector<std::string> school::grade(grade_t grade) const
{
    const auto it = roster_.find(grade);
    if (it != std::end(roster_)) {
        return it->second;
    }
    return {};
}

school::roster_t school::roster() const
{
    return roster_;
}

}  // namespace grade_school
