#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, grade_t grade_number)
{
    // Check if the student already exists in any grade
    for (const auto& grade_pair : roster_set_) {
        if ((grade_pair.second.find(name)) != grade_pair.second.end()) {
            throw std::domain_error("student already added");
        }
    }

    // Insert the student (std::set keeps names alphabetically sorted)
    (roster_set_[grade_number]).insert(name);
}

roster_t school::roster() const
{
    roster_t result{};
    for (const auto& grade_pair : roster_set_) {
        result.emplace(grade_pair.first,
                       std::vector<std::string>{grade_pair.second.begin(),
                                                grade_pair.second.end()});
    }
    return result;
}

std::vector<std::string> school::grade(grade_t grade_number) const
{
    const auto it = roster_set_.find(grade_number);
    if (it == roster_set_.end()) {
        return {};
    } else {
        return std::vector<std::string>{it->second.begin(), it->second.end()};
    }
}

}  // namespace grade_school
