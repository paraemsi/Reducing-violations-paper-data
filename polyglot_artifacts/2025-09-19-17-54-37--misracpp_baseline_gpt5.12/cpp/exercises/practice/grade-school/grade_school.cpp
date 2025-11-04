#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, school::grade_t g) {
    // Reject if the student already exists anywhere in the roster
    if (all_students_.count(name) != 0) {
        return false;
    }
    roster_sets_[g].insert(name);
    all_students_.insert(name);
    return true;
}

std::vector<std::string> school::grade(school::grade_t g) const {
    std::vector<std::string> result;
    auto it = roster_sets_.find(g);
    if (it == roster_sets_.end()) {
        return result;
    }
    result.assign(it->second.begin(), it->second.end());
    return result;
}

std::map<school::grade_t, std::vector<std::string>> school::roster() const {
    std::map<school::grade_t, std::vector<std::string>> result;
    for (const auto& kv : roster_sets_) {
        result[kv.first] = std::vector<std::string>(kv.second.begin(), kv.second.end());
    }
    return result;
}

}  // namespace grade_school
