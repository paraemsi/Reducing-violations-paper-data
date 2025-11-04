#include "grade_school.h"
#include <algorithm>
#include <iostream>
using namespace std;

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Check if the student exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (binary_search(students.begin(), students.end(), name)) {
            // Student found, don't add
            return;
        }
    }
    
    // Add the student to the specified grade
    auto& students = roster_[grade];
    // Insert in sorted order
    auto it = lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
}

std::vector<std::string> school::grade(int grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        // Return a copy of the vector
        return it->second;
    }
    // Return an empty vector
    return std::vector<std::string>();
}

std::map<int, std::vector<std::string>> school::roster() const {
    // Return a copy of the roster
    return roster_;
}

}  // namespace grade_school
