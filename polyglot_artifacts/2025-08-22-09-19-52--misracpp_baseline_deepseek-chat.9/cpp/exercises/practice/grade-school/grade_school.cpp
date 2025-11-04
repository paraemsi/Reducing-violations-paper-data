#include "grade_school.h"
#include <algorithm>
#include <set>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            // Student found, don't add again
            return;
        }
    }
    
    // Add to the grade
    roster_[grade].push_back(name);
    // Sort the students in the grade
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::vector<std::string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

std::map<int, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
