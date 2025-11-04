#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

/*  A simple school roster that
 *  - adds a student to a grade,
 *  - returns the students for a particular grade,
 *  - returns the complete roster.
 *
 *  All students have unique names within the roster.
 */
class school
{
public:
    school() = default;

    /* Add a student to a grade.
     * If the student already exists in the roster, the call is ignored.
     */
    void add(const std::string& name, std::int32_t grade);

    /* Get the list of students enrolled in a grade.
     * Returned vector is sorted alphabetically.
     */
    std::vector<std::string> grade(std::int32_t grade) const;

    /* Get the complete roster.
     * The map key is the grade (ascending order),
     * each vector is sorted alphabetically.
     */
    /*  Deliberately no [[nodiscard]] attribute here because the test-suite
     *  sometimes calls roster() merely for its side-effects (compile-time
     *  checks treat ignoring a nodiscard result as an error).
     */
    std::map<std::int32_t, std::vector<std::string>> roster() const;

private:
    std::map<std::int32_t, std::vector<std::string>> m_grade_roster {};
    std::map<std::string, std::int32_t>             m_student_grade {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
