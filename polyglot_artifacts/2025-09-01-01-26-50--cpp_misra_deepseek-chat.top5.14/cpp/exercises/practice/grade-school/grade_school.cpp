#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student is already in the all_students_ set
    if (all_students_.find(name) != all_students_.end()) {
        return;
    }
    
    // Add to the grade and sort
    roster_[grade].push_back(name);
    std::sort(roster_[grade].begin(), roster_[grade].end());
    
    // Add to all students
    all_students_.insert(name);
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(std::int32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return {};
    }
}

}  // namespace grade_school
