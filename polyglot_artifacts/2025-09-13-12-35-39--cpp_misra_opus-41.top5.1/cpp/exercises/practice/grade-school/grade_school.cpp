#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& student_name, int grade) {
    // Check if student already exists anywhere in the school
    if (all_students_.find(student_name) != all_students_.end()) {
        // Student already exists, return false to indicate failure
        return false;
    }
    
    // Add student to the grade and to the set of all students
    roster_[grade].insert(student_name);
    all_students_.insert(student_name);
    
    // Return true to indicate success
    return true;
}

std::vector<std::string> school::grade(int grade_number) const {
    // Find the grade in the roster
    auto it = roster_.find(grade_number);
    
    if (it == roster_.end()) {
        // Grade doesn't exist, return empty vector
        return std::vector<std::string>();
    }
    
    // Convert set to vector (already sorted alphabetically due to set properties)
    return std::vector<std::string>(it->second.begin(), it->second.end());
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    
    // Convert each grade's set to a vector
    for (const auto& grade_pair : roster_) {
        result[grade_pair.first] = std::vector<std::string>(
            grade_pair.second.begin(), 
            grade_pair.second.end()
        );
    }
    
    return result;
}

}  // namespace grade_school
