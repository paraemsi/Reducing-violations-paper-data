#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace grade_school {

void school::add(const string& name, int grade) {
    // Check if the student already exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (find(students.begin(), students.end(), name) != students.end()) {
            // Student found, don't add again
            return;
        }
    }
    
    // Add the student to the appropriate grade
    roster_[grade].push_back(name);
    // Sort the names for this grade
    sort(roster_[grade].begin(), roster_[grade].end());
}

vector<string> school::grade(int grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return {};
    }
}

map<int, vector<string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
