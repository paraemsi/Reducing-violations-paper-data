#include "grade_school.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <cstdint>
#include <map>

namespace grade_school {

void school::add(const std::string& name, std::uint16_t grade) {
    // Check if the student already exists using the set
    if (all_students_.find(name) != all_students_.end()) {
        // Student already exists, do nothing
        return;
    }
    
    // Add to the appropriate grade
    auto& grade_students = roster_[grade];
    // Insert in sorted order
    auto it = std::lower_bound(grade_students.begin(), grade_students.end(), name);
    grade_students.insert(it, name);
    // Add to all students set
    all_students_.insert(name);
}

std::vector<std::string> school::grade(std::uint16_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) { 
        return it->second; 
    } else { 
        return {}; 
    }
}

std::map<std::uint16_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
