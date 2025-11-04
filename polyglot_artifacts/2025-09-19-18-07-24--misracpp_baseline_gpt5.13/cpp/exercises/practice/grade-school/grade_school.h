#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to a grade. If the student already exists anywhere in the roster, ignore.
    void add(const std::string& name, int grade);

    // Get all students in a specific grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Get the full roster: grades in ascending order; students within each grade alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Maintain sorted unique names per grade.
    std::map<int, std::set<std::string>> roster_;

    // Track global uniqueness across the entire school.
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
