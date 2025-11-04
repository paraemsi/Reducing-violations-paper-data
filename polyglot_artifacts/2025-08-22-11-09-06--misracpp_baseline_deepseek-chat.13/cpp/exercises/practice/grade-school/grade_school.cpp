#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // First, check if the student exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        // Since each grade's list is sorted, we can use binary_search
        if (binary_search(students.begin(), students.end(), name)) {
            // Student found, don't add again
            return;
        }
    }
    
    // Add to the grade
    // Find the grade and insert the name while maintaining sort order
    auto& students = roster_[grade];
    // Insert the name in sorted position
    auto it = lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
}

map<int, vector<string>> school::roster() const {
    return roster_;
}

vector<string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
