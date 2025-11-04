#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name,
                 grade_t            grade_number)
{
    /*  Verify the student is not already present in any grade.   */
    for (const auto& grade_entry : roster_) {
        const auto& students = grade_entry.second;
        if (std::find(students.cbegin(), students.cend(), name) != students.cend()) {
            throw std::invalid_argument("student already present");
        }
    }

    /*  Insert the student and keep the vector sorted.   */
    auto& students_in_grade = roster_[grade_number];
    students_in_grade.push_back(name);
    std::sort(students_in_grade.begin(), students_in_grade.end());
}

roster_t school::roster() const
{
    return roster_;
}

std::vector<std::string> school::grade(grade_t grade_number) const
{
    const auto it = roster_.find(grade_number);
    if (it != roster_.cend()) {
        return it->second;
    } else {
        return {};
    }
}

}   // namespace grade_school
