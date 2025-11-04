#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>

namespace grade_school {

class school {
public:
    using grade_t  = std::int32_t;
    using roster_t = std::map<grade_t, std::vector<std::string>>;

    /* Add a student to a grade.
       Throws std::invalid_argument if the student is already present anywhere in the roster. */
    void add(const std::string& name, grade_t grade_param);

    /* Return the list of students in a specific grade, alphabetically sorted. */
    std::vector<std::string> grade(grade_t grade_param) const;

    /* Return the full school roster: grades 1,2,3…, each student list alphabetical. */
    roster_t roster() const;

private:
    std::map<grade_t, std::set<std::string>> roster_internal_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
