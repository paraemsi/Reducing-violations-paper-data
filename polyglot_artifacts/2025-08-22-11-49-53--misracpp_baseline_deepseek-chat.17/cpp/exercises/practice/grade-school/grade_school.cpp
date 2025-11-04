#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace grade_school {

void school::add(const string& name, int grade) {
    // Check if the student is already in any grade using the tracking map
    if (student_grades_.count(name) > 0) {
        // Student already exists, don't add
        return;
    }
    
    // Add the student to the specified grade
    roster_[grade].push_back(name);
    // Sort the students in the grade
    sort(roster_[grade].begin(), roster_[grade].end());
    // Track the student's grade
    student_grades_[name] = grade;
}

map<int, vector<string>> school::roster() const {
    // Return a copy of the roster where all students are sorted within their grades
    // The map itself is ordered by grade number
    return roster_;
}

vector<string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        // Return a copy of the students in the grade, which are already sorted
        return it->second;
    }
    return {};
}

}  // namespace grade_school
