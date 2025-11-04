#include "grade_school.h"
#include <algorithm>
using namespace std;

namespace grade_school {

void school::add(const string& name, int grade) {
    // Get the students for the grade
    auto& students = roster_[grade];
    // Check if the student is already in the grade
    auto it = lower_bound(students.begin(), students.end(), name);
    if (it == students.end() || *it != name) {
        // Insert the student if not found
        students.insert(it, name);
    }
    // If the student is already present, do nothing (ignore the add)
}

map<int, vector<string>> school::roster() const {
    // The roster_ is already ordered by grade, and each vector is sorted
    return roster_;
}

vector<string> school::grade(int grade_num) const {
    // Find the grade in the roster
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return {};
    }
}

}  // namespace grade_school
