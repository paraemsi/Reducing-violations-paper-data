#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level)
{
    // Prevent the same student being added twice
    if(students_.find(name) != students_.end())
    {
        return false;
    }

    (void)students_.insert(name);        // guaranteed unique after previous check
    auto& grade_set = grades_[grade_level];
    (void)grade_set.insert(name);        // std::set keeps names ordered
    return true;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    const auto it = grades_.find(grade_level);
    if(it == grades_.end())
    {
        return {};
    }

    return std::vector<std::string>(it->second.begin(), it->second.end());
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result;

    for(const auto& pair : grades_)
    {
        result[pair.first] =
            std::vector<std::string>(pair.second.begin(), pair.second.end());
    }

    return result;
}

}  // namespace grade_school
