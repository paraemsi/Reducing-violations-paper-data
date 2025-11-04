#include "grade_school.h"
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, int g) {
    // Disallow adding the same student more than once anywhere in the roster.
    for (std::map<int, std::set<std::string>>::const_iterator it = roster_.begin(); it != roster_.end(); ++it) {
        if (it->second.count(name) > 0) {
            throw std::invalid_argument("student already exists");
        }
    }
    roster_[g].insert(name);
}

std::vector<std::string> school::grade(int g) const {
    std::vector<std::string> result;
    std::map<int, std::set<std::string>>::const_iterator it = roster_.find(g);
    if (it != roster_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

school::roster_t school::roster() const {
    roster_t out;
    for (std::map<int, std::set<std::string>>::const_iterator it = roster_.begin(); it != roster_.end(); ++it) {
        out[it->first] = std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return out;
}

}  // namespace grade_school
