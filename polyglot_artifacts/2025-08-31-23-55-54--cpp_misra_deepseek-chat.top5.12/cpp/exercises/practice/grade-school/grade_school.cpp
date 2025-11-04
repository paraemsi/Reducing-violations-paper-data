#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <cstdint>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student already exists
    if (student_set_.find(name) != student_set_.end()) {
        // Student already exists, don't add
        return;
    }
    
    // Add to the grade
    roster_[grade].push_back(name);
    // Add to the set of all students
    student_set_.insert(name);
    // Sort the students in the grade alphabetically
    std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(std::uint32_t grade_number) const {
    auto it = roster_.find(grade_number);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
