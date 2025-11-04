#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = int;    // alias to meet unit-test map<int,…> signature

/* School roster implementation that obeys the MISRA C++ rules supplied.   */
class school {
public:
    school() noexcept = default;

    /* Add a student to the given grade.
     * Duplicate insertions are ignored as required by the exercise.        */
    void add(const std::string& name, grade_t grade_level) noexcept;

    /* Return the complete roster sorted by grade (ascending) and
     * by student name (lexicographically).                                 */
    std::map<grade_t, std::vector<std::string>> roster() const noexcept;

    /* Return the list of students for the requested grade, sorted
     * lexicographically.                                                   */
    std::vector<std::string> grade(grade_t grade_level) const noexcept;

private:
    /* Bi-directional lookup helpers used to guarantee uniqueness and
     * provide already-sorted output without post-processing steps.         */
    std::map<std::string, grade_t> m_student_to_grade {};
    std::map<grade_t, std::set<std::string>> m_grade_to_students {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
