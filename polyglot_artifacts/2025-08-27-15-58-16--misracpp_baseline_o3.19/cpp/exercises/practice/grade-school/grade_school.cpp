#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Ensure the student is not already present in any grade
    for (const auto& entry : data_) {
        const auto& students = entry.second;
        if (students.count(name) != 0) {
            return false;
        }
    }
    // Insert the student in the appropriate grade
    data_[grade].insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> result;
    auto it = data_.find(grade);
    if (it != data_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> full_roster;
    for (const auto& entry : data_) {
        int g = entry.first;
        const auto& students = entry.second;
        full_roster[g] = std::vector<std::string>(students.begin(), students.end());
    }
    return full_roster;
}

}  // namespace grade_school
