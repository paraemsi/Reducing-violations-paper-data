#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;
using names_t = std::vector<std::string>;
using roster_map = std::map<grade_t, names_t>;

class school {
public:
    school() = default;

    // Add a student to a grade; returns false if the student already exists in the roster
    bool add(const std::string& name, grade_t grade_level);

    // Get all students in a grade, alphabetically sorted
    names_t grade(grade_t grade_level) const;

    // Get all students in all grades, grades ascending, names alphabetically sorted
    roster_map roster() const;

private:
    std::map<grade_t, std::set<std::string>> by_grade_;
    std::unordered_set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
