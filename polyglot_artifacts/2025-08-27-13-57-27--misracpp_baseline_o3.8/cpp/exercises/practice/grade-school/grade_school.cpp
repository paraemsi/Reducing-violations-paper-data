#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, int grade)
{
    // Prevent duplicate student entries.
    if (lookup_.find(name) != lookup_.end()) {
        throw std::domain_error{"student already added"};
    }

    by_grade_[grade].insert(name);   // set keeps names sorted
    lookup_.emplace(name, grade);
}

std::vector<std::string> school::grade(int grade) const
{
    auto it = by_grade_.find(grade);
    if (it == by_grade_.end()) {
        return {};
    }
    return {it->second.begin(), it->second.end()};
}

roster_t school::roster() const
{
    roster_t result;
    for (const auto& grade_students : by_grade_) {
        int grade = grade_students.first;
        const auto& students = grade_students.second;
        result.emplace(grade,
                       std::vector<std::string>{students.begin(),
                                                students.end()});
    }
    return result;
}

}  // namespace grade_school
