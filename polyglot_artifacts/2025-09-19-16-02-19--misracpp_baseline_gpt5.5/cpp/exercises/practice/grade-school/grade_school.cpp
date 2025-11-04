#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    if (all_.count(name) != 0) {
        return false;
    }
    db_[grade].insert(name);
    all_.insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = db_.find(grade);
    if (it == db_.end()) {
        return {};
    }
    return std::vector<std::string>(it->second.begin(), it->second.end());
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> out;
    for (const auto& entry : db_) {
        out.emplace(entry.first, std::vector<std::string>(entry.second.begin(), entry.second.end()));
    }
    return out;
}

}  // namespace grade_school
