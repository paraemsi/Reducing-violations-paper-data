#include "grade_school.h"

#include <utility>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level)
{
    const bool exists = (all_students_.find(name) != all_students_.end());
    if (exists)
    {
        return false;
    }

    std::set<std::string>& set_for_grade = by_grade_[grade_level];
    const auto insert_result = set_for_grade.insert(name);
    if (!(insert_result.second))
    {
        return false;
    }

    (void)all_students_.insert(name);

    return true;
}

names_t school::grade(grade_t grade_level) const
{
    names_t result{};
    const auto it = by_grade_.find(grade_level);
    if ((it == by_grade_.end()))
    {
        return result;
    }

    const std::set<std::string>& names_set = it->second;
    result.reserve(names_set.size());
    for (const auto& s : names_set)
    {
        result.push_back(s);
    }
    return result;
}

roster_map school::roster() const
{
    roster_map result{};
    for (const auto& kv : by_grade_)
    {
        const grade_t g = kv.first;
        const std::set<std::string>& names_set = kv.second;

        names_t vec{};
        vec.reserve(names_set.size());
        for (const auto& s : names_set)
        {
            vec.push_back(s);
        }

        (void)result.emplace(g, std::move(vec));
    }
    return result;
}

}  // namespace grade_school
