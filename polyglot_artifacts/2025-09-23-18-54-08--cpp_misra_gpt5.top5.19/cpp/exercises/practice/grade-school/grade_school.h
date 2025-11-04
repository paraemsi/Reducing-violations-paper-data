#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

namespace grade_school {

class school {
public:
    using grade_t = int;
    using roster_map = std::map<grade_t, std::vector<std::string>>;

    school() = default;

    // Add a student to a grade; returns false if the student already exists in the roster.
    bool add(const std::string& name, grade_t grade_level);

    // Get the sorted list of students in a grade (alphabetical).
    std::vector<std::string> grade(grade_t grade_level) const;

    // Get the full roster: grades in ascending order; students alphabetically within each grade.
    roster_map roster() const;

private:
    std::map<grade_t, std::set<std::string>> by_grade_;
    std::unordered_set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
