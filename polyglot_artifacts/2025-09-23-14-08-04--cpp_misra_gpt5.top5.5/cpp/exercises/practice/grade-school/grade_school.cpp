#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level) noexcept
{
    const auto existing = index_.find(name);
    if ((existing != index_.end()))
    {
        return false;
    }

    student_list& students = data_[grade_level];
    const auto pos = std::lower_bound(students.begin(), students.end(), name);
    students.insert(pos, name);
    (void)index_.emplace(name, grade_level);
    return true;
}

student_list school::grade(grade_t grade_level) const noexcept
{
    const auto it = data_.find(grade_level);
    if ((it == data_.end()))
    {
        return student_list{};
    }

    return (it->second);
}

roster_map school::roster() const noexcept
{
    return (data_);
}

}  // namespace grade_school
