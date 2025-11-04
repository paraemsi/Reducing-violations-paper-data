#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// Intentionally use 'int' for grade_t to match unit test expectations.
using grade_t = int;

class school {
public:
    school() = default;

    // Add a student's name to a grade.
    // Returns true if the student was added; false if the student already exists in the roster.
    bool add(const std::string& name, grade_t grade);

    // Get the full roster: grades in ascending order and names alphabetically within each grade.
    std::map<grade_t, std::vector<std::string>> roster() const;

    // Get the list of students in a specific grade, sorted alphabetically.
    std::vector<std::string> grade(grade_t grade) const;

private:
    std::map<grade_t, std::vector<std::string>> roster_;
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
