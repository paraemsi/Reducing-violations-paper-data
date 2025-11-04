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
    // Check if the student already exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (find(students.begin(), students.end(), name) != students.end()) {
            // Student found, ignore the addition
            return;
        }
    }
    
    // Add the student to the appropriate grade
    roster_[grade].push_back(name);
    // Sort the students in the grade alphabetically
    sort(roster_[grade].begin(), roster_[grade].end());
}

vector<string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return vector<string>();
    }
}

}  // namespace grade_school
