#include "grade_school.h"
#include <algorithm>
#include <iostream>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Check if the student already exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            // According to instructions, indicate it's incorrect by not adding again
            return;
        }
    }
    
    // Add to the grade and sort
    roster_[grade].push_back(name);
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::map<int, std::vector<std::string>> school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
