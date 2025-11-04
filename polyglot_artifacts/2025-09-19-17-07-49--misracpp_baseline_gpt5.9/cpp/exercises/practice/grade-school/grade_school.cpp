#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int g) {
    // Prevent adding the same student more than once to the roster (any grade).
    if (students_.find(name) != students_.end()) {
        return false;
    }
    students_.insert(name);
    grades_[g].insert(name);
    return true;
}

std::vector<std::string> school::grade(int g) const {
    std::vector<std::string> result;
    auto it = grades_.find(g);
    if (it == grades_.end()) {
        return result;
    }
    result.assign(it->second.begin(), it->second.end());
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> out;
    for (const auto& entry : grades_) {
        int g = entry.first;
        const auto& names = entry.second;
        out[g] = std::vector<std::string>(names.begin(), names.end());
    }
    return out;
}

}  // namespace grade_school
