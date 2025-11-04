#include "grade_school.h"
#include <algorithm>

namespace grade_school {

school::school() {
    // Initialize an empty roster
}

const std::map<int, std::vector<std::string>>& school::roster() const {
    return roster_;
}

void school::add(const std::string& name, int grade) {
    // First, check if the student is already in the specified grade
    auto& grade_list = roster_[grade];
    // Check if the name is already present
    auto it = std::find(grade_list.begin(), grade_list.end(), name);
    if (it == grade_list.end()) {
        // If not present, add and sort
        grade_list.push_back(name);
        std::sort(grade_list.begin(), grade_list.end());
    }
    // If present, do nothing (indicating it's incorrect by not adding)
}

std::vector<std::string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
