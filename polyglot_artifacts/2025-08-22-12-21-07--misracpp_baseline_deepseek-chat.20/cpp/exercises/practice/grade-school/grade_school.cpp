#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace grade_school {

void school::add(const string& name, int grade) {
    // Check if the student exists in any grade
    for (const auto& entry : roster_) {
        if (entry.second.find(name) != entry.second.end()) {
            // Student already exists, do nothing
            return;
        }
    }
    // Add the student to the specified grade
    roster_[grade].insert(name);
}

set<string> school::grade(int grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return set<string>();
    }
}

map<int, set<string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
