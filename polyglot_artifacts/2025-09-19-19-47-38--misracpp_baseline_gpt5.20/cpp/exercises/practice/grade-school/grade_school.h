#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>

namespace grade_school {

using grade_t = int;

class school {
public:
    // Add a student's name to a grade. If the student already exists anywhere in the roster, throws std::invalid_argument.
    void add(const std::string& name, grade_t grade);

    // Full roster: grades in ascending order; students within each grade sorted alphabetically.
    std::map<grade_t, std::vector<std::string>> roster() const;

    // Students in a specific grade, sorted alphabetically.
    std::vector<std::string> grade(grade_t grade) const;

private:
    std::map<grade_t, std::set<std::string>> grades_;     // keeps names unique and sorted per grade
    std::map<std::string, grade_t> student_to_grade_;     // tracks if a student already exists (and in which grade)
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
