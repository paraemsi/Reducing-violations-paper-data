#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

/* Fixed-width signed type to store a grade number (1, 2, 3, …). */
using grade_t = std::int32_t;

/*  The school class manages the roster.                                                   */
class school {
public:
    school() = default;

    /* Add a new student to the given grade.
       Throws std::invalid_argument if the student already exists in any grade.           */
    void add(const std::string& name, grade_t grade_level);

    /* Return the (alphabetically) sorted list of students in the requested grade.        */
    std::vector<std::string> grade(grade_t grade_level) const;

    /* Return the complete roster: grades sorted 1,2,3… and students alphabetically.      */
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::vector<std::string>> m_roster {};  /* internal data store      */

    /* Helper to check if the student is already enrolled.                                */
    bool already_enrolled(const std::string& name) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
