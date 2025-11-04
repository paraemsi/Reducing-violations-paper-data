#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>

namespace grade_school {

using grade_t  = std::int32_t;
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    // Add a student to a grade. Throws std::domain_error if the
    // student already exists in any grade.
    void add(const std::string& name, grade_t grade_number);

    // Return the complete roster: grades sorted 1, 2, 3 … and
    // students inside each grade sorted alphabetically.
    roster_t roster() const;

    // Return the (alphabetically-sorted) list of students in a grade.
    std::vector<std::string> grade(grade_t grade_number) const;

private:
    using set_t = std::set<std::string>;
    std::map<grade_t, set_t> roster_set_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
