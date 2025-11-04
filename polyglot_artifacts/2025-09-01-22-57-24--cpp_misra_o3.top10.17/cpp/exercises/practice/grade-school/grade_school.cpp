#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add_student(const std::string& name, grade_t grade_level)
{
    /* Ensure the student is not already enrolled in any grade. */
    for (const auto& entry : grade_map_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            return false;
        }
    }

    auto& students_in_grade = grade_map_[grade_level];
    students_in_grade.push_back(name);
    std::sort(students_in_grade.begin(), students_in_grade.end());

    return true;
}

void school::add(const std::string& name, grade_t grade_level)
{
    /* Discard the boolean returned by add_student as the public add
     * interface is specified to be void. */
    (void)add_student(name, grade_level);
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    const auto it = grade_map_.find(grade_level);
    if (it != grade_map_.end()) {
        return it->second;
    } else {
        return {};
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    return grade_map_; /* return-by-value to avoid exposing internal state */
}

}  // namespace grade_school
