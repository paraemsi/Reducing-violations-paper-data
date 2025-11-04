#include "grade_school.h"
#include <algorithm>
#include <cstdint>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            // Student already exists, don't add
            return;
        }
    }
    
    // Add the student to the appropriate grade
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
