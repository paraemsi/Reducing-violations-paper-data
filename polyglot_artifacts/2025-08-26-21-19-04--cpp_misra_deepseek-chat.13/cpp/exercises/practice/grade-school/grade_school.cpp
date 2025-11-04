#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, grade_t grade) {
    // Check if the student is already in the roster
    if (all_students_.find(name) != all_students_.end()) {
        // Student already exists, do nothing
        return;
    }
    
    // Add to the grade and mark as added
    roster_[grade].push_back(name);
    all_students_.insert(name);
    // Sort the names
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::vector<std::string> school::grade(grade_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

std::map<grade_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
