#include "grade_school.h"
#include <algorithm>
#include <string>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student already exists in any grade
    if (all_students_.find(name) != all_students_.end()) {
        // Student already exists, do nothing
        return;
    }
    
    // Add to the appropriate grade
    roster_[grade].push_back(name);
    // Sort the names alphabetically
    std::sort(roster_[grade].begin(), roster_[grade].end());
    // Record the student as added
    all_students_.insert(name);
}

std::vector<std::string> school::grade(std::uint32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
