#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <set>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already in any grade
    if (all_students_.find(name) != all_students_.end()) {
        // Indicate that the addition is incorrect by simply returning without adding
        return;
    }
    
    // Add the student to the grade
    roster_[grade].insert(name);
    // Add to all students set
    all_students_.insert(name);
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    std::map<std::uint32_t, std::vector<std::string>> result;
    for (const auto& entry : roster_) {
        // Convert the set to a vector
        result[entry.first] = std::vector<std::string>(entry.second.begin(), entry.second.end());
    }
    return result;
}

std::vector<std::string> school::grade(std::uint32_t grade_number) const {
    auto it = roster_.find(grade_number);
    if (it != roster_.end()) {
        // Convert the set to a vector
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
