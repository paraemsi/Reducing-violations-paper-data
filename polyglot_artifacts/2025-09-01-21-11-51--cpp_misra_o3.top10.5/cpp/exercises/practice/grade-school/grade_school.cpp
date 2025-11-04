#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level)
{
    /* Reject duplicate student names. */
    if(name_index_.find(name) != name_index_.end())
    {
        return false;
    }

    (void)name_index_.emplace(name, grade_level);
    auto& students = roster_[grade_level];
    students.push_back(name);

    /* Keep students in alphabetical order. */
    std::sort(students.begin(), students.end());

    return true;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    const auto it = roster_.find(grade_level);
    if(it == roster_.end())
    {
        return {};
    }

    return it->second;
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result;

    /* Copy every grade, keeping alphabetical order of students. */
    for(const auto& pair : roster_)
    {
        auto students = pair.second;
        std::sort(students.begin(), students.end());
        result.emplace(pair.first, students);
    }

    return result;
}

}  // namespace grade_school
