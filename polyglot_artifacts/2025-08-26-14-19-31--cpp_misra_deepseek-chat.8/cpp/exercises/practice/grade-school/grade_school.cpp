#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student exists in any grade using all_students_
    if (all_students_.find(name) != all_students_.end()) {
        throw std::runtime_error("Student already exists in the roster");
    }
    
    // Add to the grade
    auto& students = roster_[grade];
    // Check if the student is already in this specific grade (though all_students_ should prevent this)
    if (std::find(students.begin(), students.end(), name) != students.end()) {
        throw std::runtime_error("Student already exists in this grade");
    }
    
    students.push_back(name);
    std::sort(students.begin(), students.end());
    all_students_.insert(name);
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
