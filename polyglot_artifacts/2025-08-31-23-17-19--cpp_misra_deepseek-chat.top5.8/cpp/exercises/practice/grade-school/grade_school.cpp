#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, school::grade_t grade) {
    // Check if the student is already in any grade
    auto it = student_grades_.find(name);
    if (it != student_grades_.end()) {
        // If the student exists, do nothing to indicate it's incorrect
        return;
    }
    
    // Add to the grade
    roster_[grade].insert(name);
    student_grades_[name] = grade;
}

std::map<school::grade_t, std::vector<std::string>> school::roster() const {
    std::map<school::grade_t, std::vector<std::string>> result;
    for (const auto& entry : roster_) {
        // Convert the set to a vector
        std::vector<std::string> students(entry.second.begin(), entry.second.end());
        result[entry.first] = students;
    }
    return result;
}

std::vector<std::string> school::grade(school::grade_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    } else {
        return std::vector<std::string>();
    }
}

}  // namespace grade_school
