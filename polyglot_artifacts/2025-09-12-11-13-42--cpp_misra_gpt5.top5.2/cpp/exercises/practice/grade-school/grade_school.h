#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Tests expect grade identifiers to be plain int keys.
    using grade_type = int;

    // Add a student to the given grade.
    // Returns true if added; false if the student already exists in the roster.
    bool add(const std::string& name, grade_type grade);

    // Get the full roster: grades ascending; names alphabetically within each grade.
    std::map<grade_type, std::vector<std::string>> roster() const;

    // Get the list of students in a specific grade, sorted alphabetically.
    std::vector<std::string> grade(grade_type grade_value) const;

private:
    std::map<grade_type, std::set<std::string>> by_grade_;
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
