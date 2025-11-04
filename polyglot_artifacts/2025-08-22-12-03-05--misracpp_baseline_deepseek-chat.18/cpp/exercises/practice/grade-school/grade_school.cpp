#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Get the students for the grade
    auto& students = roster_[grade];
    
    // Check if the student is already in the grade
    // Since the list is always sorted, we can use binary search
    auto it = std::lower_bound(students.begin(), students.end(), name);
    if (it != students.end() && *it == name) {
        // If found, do nothing (don't add again)
        return;
    }
    // Insert the name in the correct position to maintain sorting
    students.insert(it, name);
}

const std::vector<std::string>& school::grade(int grade) const {
    static const std::vector<std::string> empty;
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return empty;
}

std::map<int, std::vector<std::string>> school::roster() const {
    // The roster_ is always maintained with sorted vectors, so we can return it directly
    return roster_;
}

}  // namespace grade_school
