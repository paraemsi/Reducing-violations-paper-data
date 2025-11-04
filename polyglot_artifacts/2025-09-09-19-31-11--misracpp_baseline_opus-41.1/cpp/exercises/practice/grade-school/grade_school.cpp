#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& student_name, int grade) {
    // Check if student already exists in any grade
    if (all_students_.find(student_name) != all_students_.end()) {
        return;  // Student already exists, silently ignore
    }
    
    // Add student to the specified grade
    roster_[grade].insert(student_name);
    
    // Track student in all_students set
    all_students_.insert(student_name);
}

std::vector<std::string> school::grade(int grade_number) const {
    // Check if the grade exists in the roster
    auto it = roster_.find(grade_number);
    if (it != roster_.end()) {
        // Convert set to vector (already sorted alphabetically)
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    
    // Return empty vector if grade doesn't exist
    return std::vector<std::string>();
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    
    // Convert each grade's set of students to a vector
    for (const auto& grade_pair : roster_) {
        result[grade_pair.first] = std::vector<std::string>(
            grade_pair.second.begin(), 
            grade_pair.second.end()
        );
    }
    
    return result;
}

}  // namespace grade_school
