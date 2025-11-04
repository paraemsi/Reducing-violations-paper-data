#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace grade_school {

school::school() = default;

const map<int, vector<string>>& school::roster() const {
    return roster_;
}

void school::add(const string& name, int grade) {
    // First, check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        // Use binary search since each grade's students are always sorted
        if (binary_search(students.begin(), students.end(), name)) {
            // If found, don't add and return
            return;
        }
    }
    
    // Add to the appropriate grade and maintain sort order
    auto& students_in_grade = roster_[grade];
    // Insert the name in the correct position to keep the vector sorted
    auto it = lower_bound(students_in_grade.begin(), students_in_grade.end(), name);
    students_in_grade.insert(it, name);
}

vector<string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        // Return a copy of the vector which is always sorted
        return it->second;
    } else {
        return {};
    }
}

}  // namespace grade_school
