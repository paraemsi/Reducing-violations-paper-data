#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, int g) {
    // Ensure the student is not already present in any grade.
    for (const auto& entry : by_grade_) {
        if (entry.second.find(name) != entry.second.end()) {
            // Duplicate detected; ignore to indicate incorrect addition.
            return;
        }
    }
    by_grade_[g].insert(name);
}

std::vector<std::string> school::grade(int g) const {
    std::vector<std::string> result;
    auto it = by_grade_.find(g);
    if (it != by_grade_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& entry : by_grade_) {
        result[entry.first] = std::vector<std::string>(entry.second.begin(), entry.second.end());
    }
    return result;
}

}  // namespace grade_school
