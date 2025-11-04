#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace grade_school {

void school::add(const string& name, int grade) {
    // Check if the student is already in any grade
    auto it = student_grade_.find(name);
    if (it != student_grade_.end()) {
        // Student already exists, do nothing
        return;
    }
    
    // Add to the grade
    roster_[grade].push_back(name);
    // Sort the students in the grade
    sort(roster_[grade].begin(), roster_[grade].end());
    // Record the student's grade
    student_grade_[name] = grade;
}

vector<string> school::grade(int grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

map<int, vector<string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
