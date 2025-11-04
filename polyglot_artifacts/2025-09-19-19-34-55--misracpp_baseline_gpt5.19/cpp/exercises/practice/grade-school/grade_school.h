#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student's name to a grade.
    // Returns true if the student was added, false if the student already exists in the roster.
    bool add(const std::string& name, int grade);

    // Get a sorted list of all students by grade.
    // Grades are keys in ascending order; names within a grade are sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

    // Get a sorted list of all students enrolled in a specific grade.
    std::vector<std::string> grade(int grade) const;

private:
    std::map<int, std::set<std::string>> by_grade_;
    bool contains_student(const std::string& name) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
