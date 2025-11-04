#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Get the students in the grade
    auto& students = roster_[grade];
    // Check if the student is already in the grade
    auto it = std::find(students.begin(), students.end(), name);
    if (it == students.end()) {
        // If not present, add and sort
        students.push_back(name);
        std::sort(students.begin(), students.end());
    }
    // If already present, do nothing (ignore the addition)
}

std::vector<std::string> school::grade(int grade) const {
    // Find the grade in the roster
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    // Return an empty vector if the grade doesn't exist
    return {};
}

std::map<int, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
