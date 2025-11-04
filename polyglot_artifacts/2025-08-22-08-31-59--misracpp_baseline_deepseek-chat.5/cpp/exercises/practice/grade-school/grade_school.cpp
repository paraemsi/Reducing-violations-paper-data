#include "grade_school.h"
#include <algorithm>
using namespace std;

namespace grade_school {

school::school() {
    // Initialize empty roster
}

const map<int, vector<string>>& school::roster() const {
    return roster_;
}

void school::add(const string& name, int grade) {
    // Check if the student is already in any grade
    auto it = student_grade_.find(name);
    if (it != student_grade_.end()) {
        // If the student is in the same grade, do nothing
        if (it->second == grade) {
            return;
        }
        // Remove from the old grade
        int old_grade = it->second;
        auto& old_students = roster_[old_grade];
        old_students.erase(remove(old_students.begin(), old_students.end(), name), old_students.end());
    }
    
    // Update or add the student's grade
    student_grade_[name] = grade;
    auto& students = roster_[grade];
    // Check if the name is already in the target grade (shouldn't be, but just in case)
    // Insert in sorted order
    // First, remove if present to avoid duplicates
    students.erase(remove(students.begin(), students.end(), name), students.end());
    auto insert_it = lower_bound(students.begin(), students.end(), name);
    students.insert(insert_it, name);
}

vector<string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    // Return an empty vector if the grade doesn't exist
    return {};
}

}  // namespace grade_school
