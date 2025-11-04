#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already in any grade
    if (all_students_.find(name) != all_students_.end()) {
        throw std::runtime_error("Student already exists in the school");
    }
    
    // Add to the all_students_ set
    all_students_.insert(name);
    
    // Add to the specific grade and sort
    auto& students = roster_[grade];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

std::vector<std::string> school::grade(std::uint32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
