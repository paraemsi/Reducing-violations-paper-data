#include "grade_school.h"
#include <utility>      // for std::make_pair
#include <algorithm>    // for std::copy / std::sort (future-proof utility)

namespace grade_school {

void school::add(const std::string& name, grade_t grade_param)
{
    /* Check for duplicate student across all grades */
    for (auto const& grade_students : roster_internal_) {
        if (grade_students.second.find(name) != grade_students.second.end()) {
            throw std::invalid_argument("Student already in roster");
        }
    }

    (roster_internal_[grade_param]).insert(name);
}

std::vector<std::string> school::grade(grade_t grade_param) const
{
    auto const itr = roster_internal_.find(grade_param);
    if (itr == roster_internal_.end()) {
        return std::vector<std::string>();
    }

    return std::vector<std::string>(itr->second.begin(), itr->second.end());
}

school::roster_t school::roster() const
{
    roster_t result;

    for (auto const& grade_students : roster_internal_) {
        result.insert(
            std::make_pair(
                grade_students.first,
                std::vector<std::string>(
                    grade_students.second.begin(),
                    grade_students.second.end())));
    }

    return result;
}

}  // namespace grade_school
