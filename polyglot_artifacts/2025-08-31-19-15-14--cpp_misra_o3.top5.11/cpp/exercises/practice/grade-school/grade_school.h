#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    // Add a student to a grade, ignoring duplicate student names.
    void add(const std::string& name, grade_t grade_level);

    // Return the full school roster: grades in ascending order and
    // students within each grade in alphabetical order.
    std::map<grade_t, std::vector<std::string>> roster() const;

    // Return the list of students for a specific grade, alphabetically sorted.
    std::vector<std::string> grade(grade_t grade_level) const;

private:
    using students_set_t = std::set<std::string>;
    std::map<grade_t, students_set_t> data_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
