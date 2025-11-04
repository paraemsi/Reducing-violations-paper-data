#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade)
{
    // Enforce global uniqueness across the entire roster
    if ((all_students_.find(name) != all_students_.end())) {
        return false;
    }

    (void)all_students_.insert(name);

    // Insert into the grade's list in sorted order
    std::vector<std::string>& names = roster_[grade];
    auto it = std::lower_bound(names.begin(), names.end(), name);
    if ((it != names.end()) && ((*it) == name)) {
        // Should not happen due to global uniqueness check, but keep defensive
        return false;
    }

    (void)names.insert(it, name);
    return true;
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    // Vectors are maintained sorted on insertion
    return roster_;
}

std::vector<std::string> school::grade(grade_t grade) const
{
    auto it = roster_.find(grade);
    if ((it == roster_.end())) {
        return std::vector<std::string>{};
    }

    return it->second;
}

}  // namespace grade_school
