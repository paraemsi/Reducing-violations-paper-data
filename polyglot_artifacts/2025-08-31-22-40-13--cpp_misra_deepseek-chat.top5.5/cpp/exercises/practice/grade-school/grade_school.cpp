#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>
#include <set>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already present using the set
    if (all_students_.find(name) != all_students_.end()) {
        return;
    }
    
    // Add to all_students_
    all_students_.insert(name);
    
    // Insert the name in sorted order
    auto& students = roster_[grade];
    // Find where to insert to maintain order
    auto it = std::lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        // Return a copy of the vector which is always sorted
        return it->second;
    } else {
        return {};
    }
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    // The map is always ordered by key (grade), and each vector is always sorted
    return roster_;
}

}  // namespace grade_school
