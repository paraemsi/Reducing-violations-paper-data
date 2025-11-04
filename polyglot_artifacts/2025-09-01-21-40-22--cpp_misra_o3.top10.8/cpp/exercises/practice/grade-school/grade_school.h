#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using grade_t  = std::int32_t;
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    school() = default;

    /* Add a student to a grade. If the student already exists in any
       grade, the request is ignored as duplicate input. */
    void add(const std::string& name, grade_t grade_level);

    /* Return a complete, grade-ordered roster. */
    const roster_t& roster() const;

    /* Return the list of students in the requested grade. */
    std::vector<std::string> grade(grade_t grade_level) const;

private:
    roster_t students_by_grade_;

    /* Helper: determine if the student is already present anywhere
       in the roster. */
    bool student_exists(const std::string& name) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
