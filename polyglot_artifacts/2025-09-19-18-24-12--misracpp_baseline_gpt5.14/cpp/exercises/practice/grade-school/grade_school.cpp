#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    if (index_.find(name) != index_.end()) {
        return false;
    }
    db_[grade].insert(name);
    index_.emplace(name, grade);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> result;
    auto it = db_.find(grade);
    if (it == db_.end()) {
        return result;
    }
    result.assign(it->second.begin(), it->second.end());
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> out;
    for (auto it = db_.cbegin(); it != db_.cend(); ++it) {
        const int g = it->first;
        const std::set<std::string>& names = it->second;
        out[g] = std::vector<std::string>(names.begin(), names.end());
    }
    return out;
}

}  // namespace grade_school
