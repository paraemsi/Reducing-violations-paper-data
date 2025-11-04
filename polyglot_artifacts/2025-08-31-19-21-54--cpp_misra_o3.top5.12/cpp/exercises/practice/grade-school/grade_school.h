#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

/*  Alias for the complete school roster.
 *  Keys are grade numbers, values are alphabetically-sorted
 *  vectors of student names.
 */
/*  Canonical signed, 32-bit type for grade numbers */
using grade_t  = std::int32_t;

/*  Alias for the complete school roster.
 *  Keys are grade numbers, values are alphabetically-sorted
 *  vectors of student names.
 */
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    /*  Add a student to a grade.
     *  Throws std::invalid_argument if the student already exists
     *  in any grade.
     */
    void add(const std::string& name,
             grade_t            grade_number);

    /*  Return a full copy of the roster, ordered by ascending
     *  grade number, with the student names in each grade kept
     *  in alphabetical order.
     */
    roster_t roster() const;

    /*  Return an alphabetically-sorted list of students in the
     *  requested grade.  If the grade has no students an empty
     *  vector is returned.
     */
    std::vector<std::string> grade(grade_t grade_number) const;

private:
    roster_t roster_{};
};

}   // namespace grade_school

#endif   // GRADE_SCHOOL_H
