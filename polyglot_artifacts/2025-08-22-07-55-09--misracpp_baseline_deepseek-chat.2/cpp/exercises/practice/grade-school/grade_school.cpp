#include "grade_school.h"
#include <algorithm>
using namespace std;

namespace grade_school {

school::school() {
    // Initialize an empty roster
}

const map<int, vector<string>>& school::roster() const {
    return roster_;
}

void school::add(const string& name, int grade) {
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        // Use binary search since each grade's students are always sorted
        if (binary_search(students.begin(), students.end(), name)) {
            return; // Student already exists, do nothing
        }
    }
    
    // Add to the appropriate grade and insert in sorted order
    // Since we need to maintain order, we can insert at the correct position
    auto& students = roster_[grade];
    // Find where to insert to keep sorted
    auto it = lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
}

vector<string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
