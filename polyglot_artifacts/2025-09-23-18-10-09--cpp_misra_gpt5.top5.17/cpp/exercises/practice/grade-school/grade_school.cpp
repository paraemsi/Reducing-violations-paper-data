#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const Name& name, Grade level) {
    const auto dir_it = directory_.find(name);
    if ((dir_it != directory_.end())) {
        return false;
    } else {
        // Insert name in sorted position within the grade's vector
        auto& students = roster_[level];
        const auto pos = std::lower_bound(students.begin(), students.end(), name);
        students.insert(pos, name);

        (void)directory_.emplace(name, level);
        return true;
    }
}

std::vector<Name> school::grade(Grade level) const {
    const auto it = roster_.find(level);
    if ((it != roster_.end())) {
        return it->second;
    } else {
        return std::vector<Name>{};
    }
}

roster_t school::roster() const {
    return roster_;
}

}  // namespace grade_school
