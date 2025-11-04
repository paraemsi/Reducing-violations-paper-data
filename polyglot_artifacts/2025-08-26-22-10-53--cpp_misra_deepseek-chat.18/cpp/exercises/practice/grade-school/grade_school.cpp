#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, std::uint16_t grade) {
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            // Student found, don't add
            return;
        }
    }
    
    // Add the student to the specified grade
    roster_[grade].push_back(name);
    // Sort the students in the grade alphabetically
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::vector<std::string> school::grade(std::uint16_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

std::map<std::uint16_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
