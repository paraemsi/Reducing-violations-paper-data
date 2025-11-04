#include "grade_school.h"

#include <stdexcept>  // required by some toolchains for other translation units (no harm)

namespace grade_school {

void school::add(const std::string &name, std::int32_t grade_level)
{
    /* A student may only appear once in the entire roster. */
    if (all_students_.find(name) != all_students_.end())
    {
        return;
    }

    (void)all_students_.insert(name);
    (void)grades_[grade_level].insert(name);
}

std::vector<std::string> school::grade(std::int32_t grade_level) const
{
    std::vector<std::string> result {};
    auto it = grades_.find(grade_level);
    if (it != grades_.end())
    {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const
{
    std::map<std::int32_t, std::vector<std::string>> result {};
    for (const auto &pair : grades_)
    {
        result[pair.first] = std::vector<std::string>(pair.second.begin(), pair.second.end());
    }
    return result;
}

} // namespace grade_school
