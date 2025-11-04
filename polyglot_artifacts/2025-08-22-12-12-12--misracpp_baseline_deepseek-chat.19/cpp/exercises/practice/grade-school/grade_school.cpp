#include "grade_school.h"
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

namespace grade_school {

const map<int, vector<string>>& school::roster() const {
    return roster_;
}

void school::add(const string& name, int grade) {
    // Check if the student is already in the target grade
    // First, find the grade
    auto& students_in_grade = roster_[grade];
    
    // Check if the name is already present in this grade
    // Since the list is always sorted, we can use binary search
    // But to use binary_search, we need to ensure the list is sorted, which it always is
    if (binary_search(students_in_grade.begin(), students_in_grade.end(), name)) {
        // Student is already in this grade, which is invalid
        return;
    }
    
    // Also, check if the student exists in any other grade
    // The instructions say a student can't be added to the roster more than once
    for (const auto& entry : roster_) {
        // Skip the current grade we're checking
        if (entry.first == grade) continue;
        
        const auto& students = entry.second;
        if (binary_search(students.begin(), students.end(), name)) {
            // Student found in another grade, which is invalid
            return;
        }
    }
    
    // Insert the name in sorted order
    auto it = lower_bound(students_in_grade.begin(), students_in_grade.end(), name);
    students_in_grade.insert(it, name);
}

vector<string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    // Return an empty vector if the grade doesn't exist
    return vector<string>();
}

}  // namespace grade_school
