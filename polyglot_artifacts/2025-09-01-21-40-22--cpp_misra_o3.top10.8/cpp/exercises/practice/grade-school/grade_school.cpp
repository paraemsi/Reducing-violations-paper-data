#include "grade_school.h"

#include <algorithm>   // for std::find, std::sort

namespace grade_school {

void school::add(const std::string& name, grade_t grade_level)
{
    /* Reject duplicate student names to preserve uniqueness. */
    if (student_exists(name)) {
        return;
    }

    /* Insert the student and keep the grade list alphabetically ordered. */
    auto& students = students_by_grade_[grade_level];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

const roster_t& school::roster() const
{
    return students_by_grade_;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    const auto it = students_by_grade_.find(grade_level);
    if (it != students_by_grade_.end()) {
        return it->second;
    } else {
        return {};
    }
}

bool school::student_exists(const std::string& name) const
{
    for (const auto& grade_pair : students_by_grade_) {
        const auto& students = grade_pair.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            return true;
        }
    }
    return false;
}

}  // namespace grade_school
