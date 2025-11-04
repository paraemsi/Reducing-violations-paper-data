#include "grade_school.h"

#include <algorithm>  // for std::lower_bound, std::find

namespace grade_school {

bool school::add(const std::string& name, int grade)
{
    // Prevent the same student from appearing in any grade.
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            return false;  // student already enrolled somewhere
        }
    }

    // Insert the student in alphabetical order within the grade.
    auto& students = roster_[grade];
    auto pos = std::lower_bound(students.begin(), students.end(), name);
    students.insert(pos, name);
    return true;
}

std::vector<std::string> school::grade(int grade) const
{
    auto it = roster_.find(grade);
    if (it == roster_.end()) {
        return {};
    }
    return it->second;  // already alphabetical
}

std::map<int, std::vector<std::string>> school::roster() const
{
    return roster_;  // map keeps grades ordered; vectors already sorted
}

}  // namespace grade_school
