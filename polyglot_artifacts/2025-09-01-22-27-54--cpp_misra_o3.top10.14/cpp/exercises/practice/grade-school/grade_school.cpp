#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

auto school::student_exists(const std::string& name) const -> bool
{
    for (const auto& grade_entry : students_by_grade_) {
        const auto& students = grade_entry.second;
        if (std::find(students.cbegin(), students.cend(), name) != students.cend()) {
            return true;
        }
    }
    return false;
}

auto school::add(const std::string& name, grade_type grade_number) -> void
{
    if (student_exists(name)) {
        throw std::invalid_argument("student already enrolled");
    }

    auto& students = students_by_grade_[grade_number];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

auto school::grade(grade_type grade_number) const -> student_list
{
    const auto it = students_by_grade_.find(grade_number);
    if (it != students_by_grade_.cend()) {
        return it->second; // already sorted
    }

    return {};
}

auto school::roster() const -> roster_map
{
    return students_by_grade_; // map is ordered by key; vectors kept sorted
}

}  // namespace grade_school
