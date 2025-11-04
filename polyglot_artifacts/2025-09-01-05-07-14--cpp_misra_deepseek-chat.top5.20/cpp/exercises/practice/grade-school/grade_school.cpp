#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student already exists using the set
    if (all_students_.find(name) != all_students_.end()) {
        // Indicate it's incorrect by not adding the student
        return;
    }
    
    // Add to all students
    all_students_.insert(name);
    
    // Get the students for the grade and insert in sorted order
    auto& students = roster_[grade];
    // Find the insertion point to maintain order
    auto it = std::lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
}

std::vector<std::string> school::grade(std::uint32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        // The vector is always sorted, so we can return it directly
        return it->second;
    }
    // Return an empty vector
    return std::vector<std::string>();
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    // Return a copy of the roster which is always ordered correctly
    return roster_;
}

}  // namespace grade_school
