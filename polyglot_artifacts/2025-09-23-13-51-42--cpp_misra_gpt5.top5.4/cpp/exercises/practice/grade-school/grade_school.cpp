#include "grade_school.h"

#include <algorithm>
#include <utility>

namespace grade_school {

bool school::add(const std::string& student_name, grade_t grade_value)
{
    const auto insert_result = names_.insert(student_name);
    const bool did_insert = insert_result.second;

    if ((did_insert == false))
    {
        return false;
    }

    roster_[grade_value].push_back(student_name);
    return true;
}

school::roster_t school::roster() const
{
    roster_t sorted_roster{};

    for (const auto& entry : roster_)
    {
        const grade_t g = entry.first;
        std::vector<std::string> students = entry.second;

        std::sort(students.begin(), students.end());
        (void)sorted_roster.emplace(g, std::move(students));
    }

    return sorted_roster;
}

std::vector<std::string> school::grade(grade_t grade_value) const
{
    const auto it = roster_.find(grade_value);
    if ((it == roster_.end()))
    {
        return {};
    }

    std::vector<std::string> students = it->second;
    std::sort(students.begin(), students.end());
    return students;
}

}  // namespace grade_school
