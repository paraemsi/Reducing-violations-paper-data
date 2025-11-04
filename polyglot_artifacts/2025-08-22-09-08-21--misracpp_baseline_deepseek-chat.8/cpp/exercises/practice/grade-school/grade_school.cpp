#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <map>

namespace grade_school {

school::school() {
    // Initialize an empty roster
}

std::map<int, std::vector<std::string>> school::roster() const {
    // Return a copy of the roster
    return roster_;
}

void school::add(const std::string& name, int grade) {
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::runtime_error("Student already exists in the roster");
        }
    }
    
    // Add the student to the appropriate grade
    roster_[grade].push_back(name);
    // Sort the students in the grade alphabetically
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::vector<std::string> school::grade(int grade) const {
    // Return students in the requested grade, or an empty vector if the grade doesn't exist
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
