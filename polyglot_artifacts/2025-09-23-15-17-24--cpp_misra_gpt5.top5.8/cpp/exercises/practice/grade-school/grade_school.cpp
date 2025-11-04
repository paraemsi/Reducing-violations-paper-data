#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(std::string const& name, grade_type level)
{
    if ((names_.find(name) != names_.end())) {
        return false;
    } else {
        (void)names_.insert(name);
        auto& list = roster_[level];
        list.emplace_back(name);
        std::sort(list.begin(), list.end());
        return true;
    }
}

std::vector<std::string> school::grade(grade_type level) const
{
    auto const it = roster_.find(level);
    if ((it == roster_.end())) {
        return std::vector<std::string>{};
    } else {
        return it->second;
    }
}

school::roster_type school::roster() const
{
    return roster_;
}

}  // namespace grade_school
