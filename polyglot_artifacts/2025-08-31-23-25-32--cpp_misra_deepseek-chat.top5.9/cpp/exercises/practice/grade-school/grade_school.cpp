#include "grade_school.h"
#include <algorithm>
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already present in any grade
    if (all_students_.find(name) != all_students_.end()) {
        // Student found, don't add
        return;
    }
    
    // Add to all_students_ and the appropriate grade
    all_students_.insert(name);
    roster_[grade].push_back(name);
    // Sort the students in the grade alphabetically
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
