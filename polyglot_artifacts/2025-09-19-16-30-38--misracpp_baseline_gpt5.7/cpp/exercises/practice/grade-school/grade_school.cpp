#include "grade_school.h"
#include <utility>

namespace grade_school {

bool school::add(const std::string& name, int g) {
    if (enrollment_.find(name) != enrollment_.end()) {
        return false; // Student already enrolled in some grade
    }
    by_grade_[g].insert(name);
    enrollment_[name] = g;
    return true;
}

std::vector<std::string> school::grade(int g) const {
    std::vector<std::string> result;
    auto it = by_grade_.find(g);
    if (it == by_grade_.end()) {
        return result;
    }
    result.reserve(it->second.size());
    for (const auto& name : it->second) {
        result.push_back(name);
    }
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> out;
    for (const auto& entry : by_grade_) {
        int g = entry.first;
        const auto& names = entry.second;
        std::vector<std::string> vec;
        vec.reserve(names.size());
        for (const auto& name : names) {
            vec.push_back(name);
        }
        out.emplace(g, std::move(vec));
    }
    return out;
}

}  // namespace grade_school
