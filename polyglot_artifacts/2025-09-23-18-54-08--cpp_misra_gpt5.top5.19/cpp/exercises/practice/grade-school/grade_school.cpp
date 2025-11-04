#include "grade_school.h"
#include <utility>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level)
{
    const auto inserted = all_students_.insert(name);
    if (!(inserted.second)) {
        return false;
    }

    auto& students = by_grade_[grade_level];
    (void)students.insert(name);

    return true;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    std::vector<std::string> result{};
    const auto it = by_grade_.find(grade_level);
    if ((it != by_grade_.end())) {
        result.assign(it->second.begin(), it->second.end());
    } else {
        // no students in this grade; return empty vector
    }
    return result;
}

school::roster_map school::roster() const
{
    roster_map out{};
    for (const auto& kv : by_grade_) {
        std::vector<std::string> names{};
        names.assign(kv.second.begin(), kv.second.end());
        (void)out.emplace(kv.first, std::move(names));
    }
    return out;
}

}  // namespace grade_school
