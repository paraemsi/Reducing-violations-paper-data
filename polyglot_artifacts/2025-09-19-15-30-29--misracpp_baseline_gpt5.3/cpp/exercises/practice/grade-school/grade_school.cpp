#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if the student is already in any grade.
    for (const auto& kv : data_) {
        const std::set<std::string>& names = kv.second;
        if (names.find(name) != names.end()) {
            return false;
        }
    }
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
    std::map<int, std::vector<std::string>> out;
    for (const auto& kv : data_) {
        int g = kv.first;
        const std::set<std::string>& names = kv.second;
        out[g] = std::vector<std::string>(names.begin(), names.end());
    }
    return out;
}

}  // namespace grade_school
