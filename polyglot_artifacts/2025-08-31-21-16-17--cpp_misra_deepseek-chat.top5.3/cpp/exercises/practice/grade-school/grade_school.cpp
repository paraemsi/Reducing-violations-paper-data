#include "grade_school.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <set>

namespace grade_school {

school::school() {
    // Initialize empty data structures
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already enrolled
    if (enrolled_students_.find(name) != enrolled_students_.end()) {
        // Student is already in the roster, don't add
        return;
    }
    
    // Add to the appropriate grade
    auto& students = roster_[grade];
    // Insert the name in sorted order
    auto it = std::lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
    // Mark the student as enrolled
    enrolled_students_.insert(name);
}

std::vector<std::string> school::grade(std::uint32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
