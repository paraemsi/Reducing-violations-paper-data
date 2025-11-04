#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
using namespace std;

namespace grade_school {

school::school() {
    // Initialize an empty roster
}

map<int, vector<string>> school::roster() const {
    return roster_;
}

void school::add(const string& name, int grade) {
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (find(students.begin(), students.end(), name) != students.end()) {
            // If found, just return without adding
            return;
        }
    }
    
    // Add the student to the appropriate grade
    auto& students = roster_[grade];
    // Insert the name in sorted order
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
