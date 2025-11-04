#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Reject if student already present in any grade
    for (const auto& entry : roster_) {
        if (entry.second.find(name) != entry.second.end()) {
            return false;
        }
    }
    roster_[grade].insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> students;
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        students.assign(it->second.begin(), it->second.end());
    }
    return students;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> ordered;
    for (const auto& entry : roster_) {
        ordered[entry.first].assign(entry.second.begin(), entry.second.end());
    }
    return ordered;
}

}  // namespace grade_school
