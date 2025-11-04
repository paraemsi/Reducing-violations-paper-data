#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
using namespace std;

namespace grade_school {

school::school() {
    // Initialize an empty roster
}

map<int, vector<string>> school::roster() const {
    // Return a copy of the roster where each grade's list is sorted
    // Since we always keep the lists sorted when adding, we can just return the roster_
    return roster_;
}

void school::add(const string& name, int grade) {
    // Check if the student exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (find(students.begin(), students.end(), name) != students.end()) {
            throw invalid_argument("Student already exists in the roster");
        }
    }
    
    // Add the student to the grade
    roster_[grade].push_back(name);
    // Sort the list for this grade
    sort(roster_[grade].begin(), roster_[grade].end());
}

vector<string> school::grade(int grade) const {
    // Return students for the requested grade, or an empty vector if the grade doesn't exist
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        // Return a copy of the vector which is always sorted
        return it->second;
    }
    return {};
}

}  // namespace grade_school
