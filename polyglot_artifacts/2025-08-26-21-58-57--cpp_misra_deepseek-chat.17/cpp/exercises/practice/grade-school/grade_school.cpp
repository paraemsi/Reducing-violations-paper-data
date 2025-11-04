#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student already exists in any grade
    // Since all_students_ tracks all added students, we can use it to check for duplicates
    if (all_students_.find(name) != all_students_.end()) {
        throw std::runtime_error("Student already exists");
    }
    
    // Insert the student in sorted order
    auto& students = roster_[grade];
    // Find the insertion point to maintain sorted order
    auto it = std::lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
    all_students_.insert(name);
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        // The vector is always sorted, so we can return it directly
        return it->second;
    }
    return std::vector<std::string>();
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    // The map is ordered by key (grade number), and each vector is always sorted
    return roster_;
}

}  // namespace grade_school
