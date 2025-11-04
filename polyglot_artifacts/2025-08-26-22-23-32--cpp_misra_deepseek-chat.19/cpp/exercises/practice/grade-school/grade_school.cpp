#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <set>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student already exists using the set
    if (all_students_.find(name) != all_students_.end()) {
        // Student already exists, do nothing
        return;
    }
    
    // Add to all students set
    all_students_.insert(name);
    
    // Add to the appropriate grade
    auto& grade_students = roster_[grade];
    grade_students.push_back(name);
    // Sort the students alphabetically
    std::sort(grade_students.begin(), grade_students.end());
}

std::vector<std::string> school::grade(std::uint32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    // Return a copy of the roster, which is always sorted by grade number
    // and students within each grade are always sorted alphabetically
    return roster_;
}

}  // namespace grade_school
